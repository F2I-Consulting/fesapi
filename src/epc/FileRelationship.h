/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

Ce logiciel est un programme informatique servant à accéder aux données formatées à l'aide des standards Energistics. 

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA 
sur le site http://www.cecill.info.

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
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
