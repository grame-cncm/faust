#include <unordered_map>
#include <utility>

#include "Memory.hh"
namespace nlpl
{
class VectorMemory : public MemoryZone
{
    DeclareMode  fDecl;
    std::string  fType;
    std::string  fName;
    size_t       fSize;
    unsigned int fPhase;

   public:
    explicit VectorMemory(DeclareMode decl, std::string typ, std::string name, size_t size, unsigned int phase)
        : fDecl(decl), fType(std::move(typ)), fName(std::move(name)), fSize(size), fPhase(phase)
    {
    }

    std::string  name() override { return fName; }
    void         print(std::ostream& os) override { os << fType << '[' << fSize << ']' << ' ' << fName; };
    DeclareMode  declarationMode() override { return fDecl; }
    unsigned int phase() override { return fPhase; }
    void         getDependencies(std::set<Dependency>& dep) override
    {
        if (fPhase > 0 && fPhase < kFinal) {
            dep.insert({Vector(fDecl, fType, fName, fSize, 0), 0});
        }
    }
};

Memory Vector(DeclareMode decl, const std::string& typ, const std::string& name, size_t size, unsigned int phase)
{
    static std::unordered_map<std::tuple<DeclareMode, std::string, std::string, size_t, unsigned int>, Memory> gHash;
    std::tuple<DeclareMode, std::string, std::string, size_t, unsigned int> key(decl, typ, name, size, phase);

    auto p = gHash.find(key);
    if (p != gHash.end()) {
        return p->second;
    } else {
        Memory e = new VectorMemory(decl, typ, name, size, phase);
        gHash.insert({key, e});
        return e;
    }
}
}  // namespace nlpl