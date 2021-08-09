#include <unordered_map>
#include <utility>

#include "Memory.hh"
namespace nlpl {
class ScalarMemory : public MemoryZone {
    DeclareMode  fDecl;
    std::string  fType;
    std::string  fName;
    unsigned int fPhase;

   public:
    explicit ScalarMemory(DeclareMode decl, const std::string& typ, const std::string& name, unsigned int phase)
        : fDecl(decl), fType(typ), fName(name), fPhase(phase)
    {
        std::cout << (void*)this << ":ScalarMemory(" << decl << ", " << typ << ", " << name << ", " << phase << ")" << std::endl;
    }

    std::string name() override { return fName; }
    void        print(std::ostream& os) override
    {
        os << (void*)this << ':' << fType << ' ' << fName;
        if (fPhase != kFinal) {
            os << '_' << fPhase;  // print phase information when relevant
        }
    };
    DeclareMode  declarationMode() override { return fDecl; }
    unsigned int phase() override { return fPhase; }
    void         getDependencies(std::set<Dependency>& dep) override
    {
        if (fPhase > 0 && fPhase < kFinal) {
            dep.insert({Scalar(fDecl, fType, fName, 0), 0});
        }
    }
};

Memory Scalar(DeclareMode decl, const std::string& typ, const std::string& name, unsigned int phase)
{
    static std::unordered_map<std::tuple<DeclareMode, std::string, std::string, unsigned int>, Memory> gHash;
    std::tuple<DeclareMode, std::string, std::string, unsigned int>                                    key(decl, typ, name, phase);

    auto p = gHash.find(key);
    if (p != gHash.end()) {
        return p->second;
    } else {
        Memory e = new ScalarMemory(decl, typ, name, phase);
        gHash.insert({key, e});
        return e;
    }
};

}  // namespace nlpl