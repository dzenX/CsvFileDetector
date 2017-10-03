/*
* file: DatabBase.cpp
* DataBase class implementation
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "DataBase.h"

using std::ifstream;

//functor for sorting multiset of ground truth objects by areas with one key
//in reverse way
struct sort_functor {
	bool operator()(GrTruth* x1, GrTruth* x2) {
		return (x1->getArea() < x2->getArea());
	}
} rsort;

//loading ground truth object from given csv file
void DataBase::loadGrTruth(const char * file) {
	//opening given file
	ifstream src(file);
	if (!src.is_open())
		throw descriptive_exception("Not found file of Ground Truth");

	//some variables for reading from file
	int i_buff,curr_frame = 0;//i_buff - contains which data is being read from line, curr_frame contains frame_no line belongs to
	vector<GrTruth*> preGrTruth; //unsorted by areas ground truth objects
	string* buff = new string[6];//varriable contains one parsed string from .csv file
	string read, tmp;//read - string contains one line from file, tmp - string contains one instance of data in line

	//loop of reading from file
	while (!src.eof()) {
		i_buff = 0;
		std::getline(src, read);
		//skipping empty lines
		if (read.empty())
			continue;
		//making all fields of line one-style
		read += ',';

		for (int i = 0; i < read.size(); i++) {
			if (read[i] != ',') {
				//reading by symbol, skipping spaces and tabs
				if ((read[i] != ' ')&&(read[i] != '\t'))
					tmp += read[i];
				continue;
			}
			//saving one field in buff and going to next one
			buff[i_buff] = tmp;
			i_buff++;
			tmp.clear();
		}
		//writing fields in multimap and looking for errors in them
		try {
			int frame_no = std::stoi(buff[0]);
			if (curr_frame != frame_no) {
				std::sort(preGrTruth.rbegin(), preGrTruth.rend(), rsort);
				for (GrTruth* i : preGrTruth)
					GrTruthList.insert(std::pair<int, GrTruth*>(i->getFrameNo(), i));
				preGrTruth.clear();
				curr_frame = frame_no;
			}
			string obj_class = buff[1];
			int left = std::stoi(buff[2]);
			int top = std::stoi(buff[3]);
			int width = std::stoi(buff[4]);
			int height = std::stoi(buff[5]);
			if ((left < 0) || (top < 0) || (width < 0) || (height < 0))
				throw descriptive_exception("Invalid bounding box");
			BoundBox currentBoundBox(left, top, width, height);
			//GrTruthList.insert(std::pair<int, GrTruth*>(frame_no, new GrTruth(frame_no, obj_class, currentBoundBox)));
			preGrTruth.push_back(new GrTruth(frame_no, obj_class, currentBoundBox));
		}
		catch (std::exception ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	if (preGrTruth.size() > 0) {
		std::sort(preGrTruth.rbegin(), preGrTruth.rend());
		for (GrTruth* i : preGrTruth)
			GrTruthList.insert(std::pair<int, GrTruth*>(i->getFrameNo(), i));
		preGrTruth.clear();
	}
	src.close();
}

//load candidates from file
void DataBase::loadCandidates(const char * file) {
	ifstream src(file);
	if (!src.is_open())
		throw descriptive_exception("Not found file of Candidates");
	int i_buff;
	string* buff = new string[7];
	string read, tmp;
	while (!src.eof()) {
		i_buff = 0;
		std::getline(src, read);
		if (read.empty())
			continue;
		read += ',';
		for (int i = 0; i < read.size(); i++) {
			if (read[i] != ',') {
				if ((read[i] != ' ') && (read[i] != '\t'))
					tmp += read[i];
				continue;
			}
			buff[i_buff] = tmp;
			i_buff++;
			tmp.clear();
		}
		try {
			int frame_no = std::stoi(buff[0]);
			string obj_class = buff[1];
			double conf = std::stod(buff[2]);
			int left = std::stoi(buff[3]);
			int top = std::stoi(buff[4]);
			int width = std::stoi(buff[5]);
			int height = std::stoi(buff[6]);
			if ((left < 0) || (top < 0) || (width < 0) || (height < 0))
				throw descriptive_exception("Invalid bounding box");
			if ((conf < 0) || (conf > 1))
				throw descriptive_exception("Invalid confidence");
			BoundBox currentBoundBox(left, top, width, height);
			CandidateList.insert(std::pair<int, Candidate*>(frame_no, new Candidate(frame_no, obj_class, currentBoundBox, conf)));
		}
		catch (std::exception ex) {
			std::cout << ex.what() << std::endl;
		}
	}
	src.close();
}

//show ground truth
void DataBase::viewGrTruth() {
	for (auto it = GrTruthList.begin(); it != GrTruthList.end(); ++it) {
		it->second->print();
		std::cout << "\n";
	}
}

//show candidates
void DataBase::viewCandidates() {
	for (auto it = CandidateList.begin(); it != CandidateList.end(); ++it) {
		it->second->print();
		std::cout << "\n";
	}
}

void DataBase::detect(const char* file) {
	//resulting file
	std::ofstream detected;
	detected.open(file);

	//possible errors
	if (!detected.is_open())
		throw descriptive_exception("Error in opening result file");
	if (GrTruthList.size() == 0)
		throw descriptive_exception("No Ground Truth objects");
	if (CandidateList.size() == 0)
		throw descriptive_exception("No Candidate objects");

	//additional variables
	vector<Candidate*> cnd_of_range;
	string buff;
	detected_gr_tr = 0;
	detected_cnd = 0;
	
	//taking ground truth object and searching all matching by frame_no candidates
	for (auto gr_it = GrTruthList.begin(); gr_it != GrTruthList.end(); ++gr_it) {
		std::pair<std::multimap<int, Candidate*>::const_iterator, std::multimap<int, Candidate*>::const_iterator> range 
			= CandidateList.equal_range(gr_it->first);
		cnd_of_range.clear();
		//detecting from possible range
		for (auto it = range.first; it != range.second; ++it) {
			//checking class and frame_no of candidate
			if (gr_it->second->allowToCompare(it->second))
				//counting area realtions
				if (gr_it->second->detector(it->second)) 
					//adding to possible candidates
					cnd_of_range.push_back(it->second);
		}
		//Detection by confidence
		Candidate* Candidate_of_range = chooseByConfidence(cnd_of_range);
		if (Candidate_of_range) {
			Result.insert(std::pair<int, Candidate*>(gr_it->first, Candidate_of_range));
			detected_gr_tr++;
			detected_cnd++;
			//saving result in file
			buff.clear();
			buff += std::to_string(Candidate_of_range->getFrameNo());
			buff += ", ";
			buff += Candidate_of_range->getObjClass();
			buff += ", ";
			buff += std::to_string(Candidate_of_range->getConfidence());
			buff += ", ";
			buff += std::to_string(Candidate_of_range->getDetectionCo());
			buff += ", ";
			buff += Candidate_of_range->getCoords();
			buff += " -> ";
			buff += std::to_string(gr_it->second->getFrameNo());
			buff += ", ";
			buff += gr_it->second->getObjClass();
			buff += ", ";
			buff += gr_it->second->getCoords();
			buff += '\n';
			detected << buff;
		}
	}
	detected.close();
}

//choosing candidates by highest confidence
Candidate * DataBase::chooseByConfidence(vector<Candidate*> cnd)
{
	if (cnd.size() > 0) {
		Candidate* res = cnd[0];
		for (Candidate* current : cnd) 
			if (current->getConfidence() > res->getConfidence())
				res = current;
		return res;
	}
	return nullptr;
}

void DataBase::viewNumOfDetected() {
	std::cout << "Number of detected ground truth objects = " << std::to_string(detected_gr_tr) << std::endl;
	std::cout << "Number of detected candidates objects = " << std::to_string(detected_cnd) << std::endl;
	std::cout << "Number of undetected ground truth objects = " << std::to_string(GrTruthList.size() - detected_gr_tr) << std::endl;
	std::cout << "Number of undetected ground truth objects = " << std::to_string(CandidateList.size() - detected_cnd) << std::endl;
}
