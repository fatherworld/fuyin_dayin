#include "prasexml.h"

void printSchoolXml() {
	TiXmlDocument doc;  
	const char * xmlFile = "./TestXml/xmlFiles/school2.xml";   
	if (doc.LoadFile(xmlFile)) {    
		doc.Print();  
	} else {
		cout << "can not parse xml conf/school.xml" << endl;
	}   
}

void readSchoolXml() {
	const char * xmlFile = "./TestXml/xmlFiles/school2.xml";
	TiXmlDocument doc;                              
	if (doc.LoadFile(xmlFile)) {
		doc.Print();
	} else {
		cout << "can not parse xml conf/school2.xml" << endl;
		return;
	}

	TiXmlElement* rootElement = doc.RootElement();  //School元素  
	TiXmlElement* classElement = rootElement->FirstChildElement();  // Class元素
	TiXmlElement* studentElement = classElement->FirstChildElement();  //Students  

	for (; studentElement != NULL; studentElement = studentElement->NextSiblingElement() ) {
		TiXmlAttribute* attributeOfStudent = studentElement->FirstAttribute();  //获得student的name属性  
		for (;attributeOfStudent != NULL; attributeOfStudent = attributeOfStudent->Next() ) {
			cout << attributeOfStudent->Name() << " : " << attributeOfStudent->Value() << std::endl;       
		}                                 

		TiXmlElement* studentContactElement = studentElement->FirstChildElement();//获得student的第一个联系方式 

		for (; studentContactElement != NULL; studentContactElement = studentContactElement->NextSiblingElement() ) {
			string contactType = studentContactElement->Value();
			string contactValue = studentContactElement->GetText();


			cout << contactType<< " : " << contactValue <<endl;           
		}   
	} 
}