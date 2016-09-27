#include "q2tallyVotes.h"
//#include "voter.h"
#include "printer.h"


TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	ownerLock.acquire();
		if(inuse){
			bLock.wait(ownerLock);
//			cout << "releasing" << endl;
			if(bLock.empty()) inuse = 0;
		}
		if(curMember == 0){
			picOrStatue = 0;
		}
		++curMember;
		printer.print(id, Voter::States::Vote, ballot);
//		cout << "id " << id << " " << curMember << " " << ballot << endl;
		if(ballot == Tour::Picture){
			--picOrStatue;
		}else{
			++picOrStatue;
		}

		if(curMember == group){
//			cout << "release" << endl;
			inuse = 1;
		//	picOrStatue = 0;
			printer.print(id, Voter::States::Complete);
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
//			tallyLock.signal();
//			tallyLock.signal();
		//	bLock.signal();
		//	inuse = 0; 
		}else{
	//		inuse = 1;
			printer.print(id, Voter::States::Block, curMember);
			if(!bLock.empty()) bLock.signal();
			tallyLock.wait(ownerLock);
			printer.print(id, Voter::States::Unblock, (curMember - 1));
			//add finish print
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
		}
		--curMember;
	//	if(!tallyLock.empty()){
		//	tallyLock.signal();
	//	}else{
		if(!tallyLock.empty()){
			tallyLock.signal();
		}else if(!bLock.empty()){
			bLock.signal();
		}else{
			inuse = 0;
		}
	//	}
		ownerLock.release();
//      cout << "value " << picOrStatue << endl;
        if(picOrStatue == 0){
                std::cerr << "equal votes" << std::endl;
                return Tour::Picture;
        }
        if(picOrStatue > 0){
//              picOrStatue = 0;
                return Tour::Statue;
        }else{
//              picOrStatue = 0;
                return Tour::Picture;
        }
}

