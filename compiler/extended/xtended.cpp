
#include "xtended.hh"
#include "floats.hh"
    
void xtended::prepareTypeArgsResult(::Type result, 
                            const list<ValueInst*>& args, 
                            vector< ::Type> const& types,
                            Typed::VarType& result_type, 
                            vector<Typed::VarType>& arg_types, 
                            list<ValueInst*>& casted_args)
{
    if (result->nature() == kInt) {
        result_type = Typed::kInt; 
    } else {
        result_type = itfloat();
    }
    
    vector< ::Type>::const_iterator it1;
    list<ValueInst*>::const_iterator it2 = args.begin();
    
    for (it1 = types.begin(); it1 != types.end(); it1++, it2++) {
        if (((*it1)->nature() == kInt)) {
            // Possibly cast arguments
            casted_args.push_back(InstBuilder::genCastNumInst((*it2), InstBuilder::genBasicTyped(itfloat())));
        } else {
            casted_args.push_back((*it2));
        }
        // Force type to float/double
        arg_types.push_back(itfloat());
    }
}


