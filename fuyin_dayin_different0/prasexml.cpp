#include "prasexml.h"
int getXmlPoint2s(string xmlpath,vector<p2>& p2s,int& charNumbers)
{
	int res = 0;
	TiXmlDocument doc;   
	if (doc.LoadFile(xmlpath.c_str())) {    
		cout<<"sucess to load xml file"<<endl;
	} else {
		cout << "can not parse xml file" << endl;
		res = -1;
		return res;
	}
	TiXmlElement* rootElement = doc.RootElement();
	TiXmlElement* characters = rootElement->FirstChildElement();//charactersÔªËØ
	//int charNumbers = 0;
	TiXmlAttribute* Nums = characters->FirstAttribute();
	String charNumbers_str = Nums->Value();
	charNumbers = stoi(charNumbers_str);
	TiXmlElement* curCh = characters->NextSiblingElement();
	for(;curCh != NULL;curCh = curCh->NextSiblingElement())
	{
		p2 p;
		Point p1,p2;
		TiXmlAttribute* attributeOfCh = curCh->FirstAttribute()->Next();	
		p1.y = atoi(attributeOfCh->Value());
		attributeOfCh = attributeOfCh->Next();
		p1.x = atoi(attributeOfCh->Value());
		attributeOfCh = attributeOfCh->Next();
		p2.y = atoi(attributeOfCh->Value());
		attributeOfCh = attributeOfCh->Next();
		p2.x = atoi(attributeOfCh->Value());

		p.one = p1;
		p.two = p2;
		p2s.push_back(p);
	}
	return res;
}
