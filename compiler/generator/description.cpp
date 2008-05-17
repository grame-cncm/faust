//------------------------------------
// generation of an xml description
//------------------------------------

#include "description.hh"
#include "Text.hh"

/**
 * removes enclosing quotes and transforms '<', '>' and '&' characters
 */
static string xmlize(const string& src)
{
    string dst;
    for (unsigned int i=0; i<src.size(); i++) {
        if (src[i] == '"' & (i==0 | i==src.size()-1)) {
            // nothing to do just skip the quotes
        } else {
            switch (src[i]) {
                case '<' : dst += "&lt;"; break;
                case '>' : dst += "&gt;"; break;
                case '&' : dst += "&amp;"; break;
                default :  dst += src[i];
            }
        }
    }
    return dst;
}

void Description::print(int n, ostream& fout)
{
	list<string>::iterator 	s;
	list<int>::iterator 	t;
	
	tab(n,fout); fout << "<faust>";
		
		tab(n+1,fout);	fout << "<name>" 		<< xmlize(fName) 		<< "</name>";
		tab(n+1,fout);	fout << "<author>" 	    << xmlize(fAuthor) 		<< "</author>";
		tab(n+1,fout);	fout << "<copyright>" 	<< xmlize(fCopyright) 	<< "</copyright>";
		tab(n+1,fout);	fout << "<license>" 	<< xmlize(fLicense) 	<< "</license>";
		tab(n+1,fout);	fout << "<version>" 	<< xmlize(fVersion) 	<< "</version>";
		tab(n+1,fout);	fout << "<inputs>" 	    << fInputs 		        << "</inputs>";
		tab(n+1,fout);	fout << "<outputs>" 	<< fOutputs 	        << "</outputs>";
	
		tab(n+1,fout);	fout << "<ui>";

			// active widget list
			tab(n+2,fout);	fout << "<activewidgets>";
				tab(n+3,fout);	fout << "<count>" << fActiveWidgetCount << "</count>";
				for (s = fActiveLines.begin(); s != fActiveLines.end(); s++) {
					tab(n+3, fout); fout << *s;
				}
			tab(n+2,fout);	fout << "</activewidgets>";

			tab(n+2,fout);
			
			// passive widget list
			tab(n+2,fout);	fout << "<passivewidgets>";
				tab(n+3,fout);	fout << "<count>" << fPassiveWidgetCount << "</count>";
				for (s = fPassiveLines.begin(); s != fPassiveLines.end(); s++) {
					tab(n+3, fout); fout << *s;
				}
			tab(n+2,fout);	fout << "</passivewidgets>";
	
			
			tab(n+2,fout);
			
			// widget layout 
			tab(n+2,fout);	fout << "<layout>";
				for (	t = fLayoutTabs.begin(), s = fLayoutLines.begin();
						s != fLayoutLines.end(); t++, s++) {
					tab(n+3+*t, fout); fout << *s;
				}
			tab(n+2,fout);	fout << "</layout>";
		
		tab(n+1,fout);	fout << "</ui>";


	tab(n,fout); fout << "</faust>" << endl;
	 
}
 
void Description::ui(Tree t)
{
	addGroup(0,t);
}


void Description::addGroup(int level, Tree t)
{
	Tree 	label, elements, varname, sig;
	const char*	groupnames[] = {"vgroup", "hgroup", "tgroup"};
	
	if (isUiFolder(t, label, elements)) {
	
		const int		orient = tree2int(left(label));
		const char * 	str = tree2str(right(label));

		addLayoutLine(level, subst("<group type=\"$0\">", groupnames[orient]));
		addLayoutLine(level+1, subst("<label>$0</label>", xmlize(str)));
		while (!isNil(elements)) {
			addGroup(level+1, right(hd(elements)));
			elements = tl(elements);
		}		
		addLayoutLine(level, "</group>");
		
	} else if (isUiWidget(t, label, varname, sig)) {
			
		int w = addWidget(label, varname, sig);
		addLayoutLine(level, subst("<widgetref id=\"$0\" />", T(w)));
		
	} else {
		
		fprintf(stderr, "error in user interface generation 2\n");
		exit(1);
		
	}
}

void Description::tab (int n, ostream& fout)
{
	fout << '\n';
	while (n--)	fout << '\t'; 
}
	
int Description::addWidget(Tree label, Tree varname, Tree sig)
{
	Tree path, c, x, y, z;
	
	// add an active widget description
	
	if ( isSigButton(sig, path) ) 					{
	
		fWidgetID++;
		fActiveWidgetCount++;
		addActiveLine(subst("<widget type=\"button\" id=\"$0\">", T(fWidgetID)));
			addActiveLine(subst("\t<label>$0</label>", xmlize(tree2str(label))));
			addActiveLine(subst("\t<var>$0</var>", tree2str(varname)));
		addActiveLine("</widget>");
			
	} else if ( isSigCheckbox(sig, path) ) 			{
	
		fWidgetID++;
		fActiveWidgetCount++;
		addActiveLine(subst("<widget type=\"checkbox\" id=\"$0\">", T(fWidgetID)));
			addActiveLine(subst("\t<label>$0</label>", xmlize(tree2str(label))));
			addActiveLine(subst("\t<var>$0</var>", tree2str(varname)));
		addActiveLine("</widget>");
			
	} else if ( isSigVSlider(sig, path,c,x,y,z) )	{
	
		fWidgetID++;
		fActiveWidgetCount++;
		addActiveLine(subst("<widget type=\"vslider\" id=\"$0\">", T(fWidgetID)));
			addActiveLine(subst("\t<label>$0</label>", 		xmlize(tree2str(label))));
			addActiveLine(subst("\t<varname>$0</varname>", 	tree2str(varname)));
			addActiveLine(subst("\t<init>$0</init>", 		T(tree2float(c))));
			addActiveLine(subst("\t<min>$0</min>", 			T(tree2float(x))));
			addActiveLine(subst("\t<max>$0</max>", 			T(tree2float(y))));
			addActiveLine(subst("\t<step>$0</step>", 		T(tree2float(z))));
		addActiveLine("</widget>");
			
	} else if ( isSigHSlider(sig, path,c,x,y,z) )	{
	
		fWidgetID++;
		fActiveWidgetCount++;
		addActiveLine(subst("<widget type=\"hslider\" id=\"$0\">", T(fWidgetID)));
			addActiveLine(subst("\t<label>$0</label>", 		xmlize(tree2str(label))));
			addActiveLine(subst("\t<varname>$0</varname>", 	tree2str(varname)));
			addActiveLine(subst("\t<init>$0</init>", 		T(tree2float(c))));
			addActiveLine(subst("\t<min>$0</min>", 			T(tree2float(x))));
			addActiveLine(subst("\t<max>$0</max>", 			T(tree2float(y))));
			addActiveLine(subst("\t<step>$0</step>", 		T(tree2float(z))));
		addActiveLine("</widget>");
			
	} else if ( isSigNumEntry(sig, path,c,x,y,z) )	{
	
		fWidgetID++;
		fActiveWidgetCount++;
		addActiveLine(subst("<widget type=\"nentry\" id=\"$0\">", T(fWidgetID)));
			addActiveLine(subst("\t<label>$0</label>", 		xmlize(tree2str(label))));
			addActiveLine(subst("\t<varname>$0</varname>", 	tree2str(varname)));
			addActiveLine(subst("\t<init>$0</init>", 		T(tree2float(c))));
			addActiveLine(subst("\t<min>$0</min>", 			T(tree2float(x))));
			addActiveLine(subst("\t<max>$0</max>", 			T(tree2float(y))));
			addActiveLine(subst("\t<step>$0</step>", 		T(tree2float(z))));
		addActiveLine("</widget>");

			
	// add a passive widget description
	
	} else if ( isSigVBargraph(sig,path,x,y,z) )	{
	
		fWidgetID++;
		fPassiveWidgetCount++;
		addPassiveLine(subst("<widget type=\"vbargraph\" id=\"$0\">", T(fWidgetID)));
			addPassiveLine(subst("\t<label>$0</label>", 	xmlize(tree2str(label))));
			addPassiveLine(subst("\t<varname>$0</varname>", tree2str(varname)));
			addPassiveLine(subst("\t<min>$0</min>", 		T(tree2float(x))));
			addPassiveLine(subst("\t<max>$0</max>", 		T(tree2float(y))));
		addPassiveLine("</widget>");
		
	} else if ( isSigHBargraph(sig,path,x,y,z) )	{
	
		fWidgetID++;
		fPassiveWidgetCount++;
		addPassiveLine(subst("<widget type=\"hbargraph\" id=\"$0\">", T(fWidgetID)));
			addPassiveLine(subst("\t<label>$0</label>", 	xmlize(tree2str(label))));
			addPassiveLine(subst("\t<varname>$0</varname>", tree2str(varname)));
			addPassiveLine(subst("\t<min>$0</min>", 		T(tree2float(x))));
			addPassiveLine(subst("\t<max>$0</max>", 		T(tree2float(y))));
		addPassiveLine("</widget>");
		
	} else {
		fprintf(stderr, "Error describing widget : unrecognized expression\n");
		exit(1);
	}

	return fWidgetID;
}



