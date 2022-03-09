#ifndef MatchMaker_h
#define MatchMaker_h
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "PersonProfile.h"
#include "provided.h"
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <chrono>
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
    static inline bool byEmail(const EmailCount &e1, const EmailCount &e2){
        if(e1.count == e2.count) return e1.email < e2.email;
        return (e1.count > e2.count);
    }
    //TODO: remove this code before turning in
    //from stack overflow
    template <
        class result_t   = std::chrono::milliseconds,
        class clock_t    = std::chrono::steady_clock,
        class duration_t = std::chrono::milliseconds
    >
    static inline auto since(std::chrono::time_point<clock_t, duration_t> const& start)
    {
        return std::chrono::duration_cast<result_t>(clock_t::now() - start);
    }
    //TODO: figure out why m_set does not work when it is a private member variable.
    //    std::unordered_set<std::string> m_set;

};

#endif
