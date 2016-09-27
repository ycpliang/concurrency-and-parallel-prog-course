#include "q2tallyVotes.h"
//#include "voter.h"
#include "printer.h"


TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : uBarrier(group), curMember(0), group(group),picOrStatue(0), printer(printer) {}

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
		if(curMember == 0){
			picOrStatue = 0;
		}
		++curMember;
		printer.print(id, Voter::States::Vote, ballot);
		if(ballot == Tour::Picture){
			--picOrStatue;
		}else{
			++picOrStatue;
		}

		if(curMember == group){
			printer.print(id, Voter::States::Complete);
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
//			ownerLock.P();
			uBarrier::block();
		}else{
			printer.print(id, Voter::States::Block, curMember);
			uBarrier::block();
			printer.print(id, Voter::States::Unblock, (curMember - 1));
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
		}
		--curMember;
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

