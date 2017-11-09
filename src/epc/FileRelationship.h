/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

Ce logiciel est un programme informatique servant � acc�der aux donn�es format�es � l'aide des standards Energistics. 

Ce logiciel est r�gi par la licence CeCILL-B soumise au droit fran�ais et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffus�e par le CEA, le CNRS et l'INRIA 
sur le site http://www.cecill.info.

En contrepartie de l'accessibilit� au code source et des droits de copie,
de modification et de redistribution accord�s par cette licence, il n'est
offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les conc�dants successifs.

A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
associ�s au chargement,  � l'utilisation,  � la modification et/ou au
d�veloppement et � la reproduction du logiciel par l'utilisateur �tant 
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe � 
manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
logiciel � leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement, 
� l'utiliser et l'exploiter dans les m�mes conditions de s�curit�. 

Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accept� les
termes.
-----------------------------------------------------------------------*/
#ifndef FILE_RELATIONSHIP_H
#define FILE_RELATIONSHIP_H

#include <vector>

#include "Relationship.h"

namespace epc
{
	/**
	* This class intends to represent any rel file of the package.
	*/
	class FileRelationship
	{
	private:
		std::string pathName;
		std::vector<Relationship> relationship;

	public:
		// CONSTRUCTORS
		FileRelationship();
		FileRelationship(const Relationship & frRelationship);
		FileRelationship(const std::vector<Relationship> & frRelationship);
		~FileRelationship() {}

		// ACCESSORS
		bool isEmpty() const;
		std::string getPathName() const;
		std::vector<Relationship> getAllRelationship() const;
		Relationship getIndexRelationship(const int & index) const;
		std::string toString() const;

		void setPathName(const std::string & frPathName);
		void addRelationship(const Relationship & frRelationship);

		/**
		* Read a relationships part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
