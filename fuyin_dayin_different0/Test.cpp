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

	TiXmlElement* rootElement = doc.RootElement();  //SchoolԪ��  
	TiXmlElement* classElement = rootElement->FirstChildElement();  // ClassԪ��
	TiXmlElement* studentElement = classElement->FirstChildElement();  //Students  

	for (; studentElement != NULL; studentElement = studentElement->NextSiblingElement() ) {
		TiXmlAttribute* attributeOfStudent = studentElement->FirstAttribute();  //���student��name����  
		for (;attributeOfStudent != NULL; attributeOfStudent = attributeOfStudent->Next() ) {
			cout << attributeOfStudent->Name() << " : " << attributeOfStudent->Value() << std::endl;       
		}                                 

		TiXmlElement* studentContactElement = studentElement->FirstChildElement();//���student�ĵ�һ����ϵ��ʽ 

		for (; studentContactElement != NULL; studentContactElement = studentContactElement->NextSiblingElement() ) {
			string contactType = studentContactElement->Value();
			string contactValue = studentContactElement->GetText();


			cout << contactType<< " : " << contactValue <<endl;           
		}   
	} 
}