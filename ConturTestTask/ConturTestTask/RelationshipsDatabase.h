/******************************************************************************
* File: RelationshipsDatabase.h
* Description: Describes relationships between humans (only sympathy)
* Created: 06 Mar 2015
* Copyright: (C) PirateTigo
* Author: Artem Tarakanovskiy
* Email: piratetigo@gmail.com

******************************************************************************/

#pragma once

#include "Graph.h"

namespace relationships
{
	/**
	* @class RelationshipsDatabase
	* Database for storage and submission of relationships between humans.
	* @note For showing information need use std::ostream objects, e.g. std::cout.
	* @note You are can to load information into database after instantiation later.
	*/
	class RelationshipsDatabase
	{		
	public:
		/**
		* Empty consructor
		*/
		RelationshipsDatabase();
		/**
		* Constructor
		* @param ifNames - input file stream linked with file that has Names info.
		* @param ifRelationships - input file stream linked with file that has Relationships info.
		*/
		RelationshipsDatabase(std::ifstream &ifNames, std::ifstream &ifRelationships);

		/**
		* Loading information into database
		* @param ifNames - input file stream linked with file that has Names info
		* @param ifRelationships - input file stream linked with file that has Relationships info
		*/
		void Load(std::ifstream &ifNames, std::ifstream &ifRelationships);
		/**
		* Clearing database		
		*/
		void Clear();
		/**
		* Showing all unloved humans contained into database
		* @param roOut - output stream, output will be carried out through him
		*/
		void ShowUnloved(std::ostream &roOut) const;
		/**
		* Showing all wretched humans contained into database
		* @param roOut - output stream, output will be carried out through him
		*/
		void ShowWretched(std::ostream &roOut) const;
		/**
		* Showing all beloved humans contained into database
		* @param roOut - output stream, output will be carried out through him
		*/
		void ShowBeloved(std::ostream &roOut) const;
		/**
		* Showing all humans contained into database
		* @param roOut - output stream, output will be carried out through him
		*/
		void ShowAll(std::ostream &roOut) const;
		/**
		* Showing all relations between humans contained into database
		* @param roOut - output stream, output will be carried out through him
		*/
		void ShowRelations(std::ostream &roOut) const;

		/**
		* Destructor
		*/
		~RelationshipsDatabase();
	
	private:
		/// Graph with information of relation between humans
		Graph *m_gRelations;
		
		/**
		* Searching vertexes for given name within given list of vertexes
		* @ pcName - given name
		* @ rlVertexes - given list of vertexes
		*/
		Vertex *Search(const char* pcName, const std::list<Vertex *> &rlVertexes) const;
	};
}