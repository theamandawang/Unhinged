#ifndef MatchMaker_h
#define MatchMaker_h
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#include "provided.h"
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <string>
//needs to be as fast as possible
//ANY STL containers allowed bleessss
class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase * m_data;
    const AttributeTranslator * m_at;
    static inline bool byEmail(EmailCount e1, EmailCount e2){
        if(e1.count == e2.count) return e1.email < e2.email;
        return (e1.count > e2.count);
    }
    //TODO: figure out why m_set does not work when it is a private member variable.
    //    std::unordered_set<std::string> m_set;

};

#endif
