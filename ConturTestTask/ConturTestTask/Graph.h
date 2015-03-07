/******************************************************************************
* File: Graph.h
* Description: Describes graph of relationships
* Created: 06 Mar 2015
* Copyright: (C) PirateTigo
* Author: Artem Tarakanovskiy
* Email: piratetigo@gmail.com

******************************************************************************/

#pragma once

#include "Vertex.h"

namespace relationships
{
	/**
	* @class Graph
	* Oriented graph of relationships
	* @note Vertexes - is humans
	* @note Edges - is sympathy
	*/
	class Graph
	{		
	public:
		/**
		* @class iterator
		* iterator for Graph
		*/
		class iterator
		{
			friend class Graph;			

		public:
			/**
			* Copy constructor
			* @param riOther - copy source iterator
			*/
			iterator(iterator &riOther);

			/**
			* Assignment operator
			* @param riOther - copy source iterator
			*/
			iterator &operator=(iterator &riOther);
			/**
			* Increment operator
			*/
			iterator &operator++();
			/**
			* Comparison operator
			* @param riOther - iterator to compare
			*/
			bool operator==(iterator &riOther) const;
			/**
			* Inequality operator
			* @param riOther - iterator to compare
			*/
			bool operator!=(iterator &riOther) const;
			/**
			* Dereference operator
			*/
			Vertex *operator*() const;

			/**
			* Destructor
			*/
			~iterator();

		private:
			/// List of participants bypass
			std::list<Vertex *> *m_plVertexes;
			/// List iterator
			std::list<Vertex *>::iterator m_itVertexes;

			/**
			* Hidden constructor
			* @param pvStartPosition - start position for bypass
			* @param pgParent - graph that will be carried out round
			*/
			iterator(Vertex *pvStartPosition, Graph *pgParent);
		};

		/**
		* Constructor
		* @param rlVertexes - human names
		* @param rlEdges - relationships within this people
		*/
		Graph(std::list<Vertex *> &rlVertexes, std::list<Edge *> &rlEdges);

		/**
		* First element of graph collection
		*/
		iterator begin();
		/**
		* Element following the last element of graph collection
		*/
		iterator end();

		/**
		* Getting list of unloved humans who are within graph collection
		*/
		std::list<Vertex *> *GetUnloved() const;
		/**
		* Getting list of wretched humans who are within graph collection
		*/
		std::list<Vertex *> *GetWretched() const;
		/**
		* Getting list of beloved humans who are within graph collection
		*/
		std::list<Vertex *> *GetBeloved() const;
		/**
		* Getting all humans who are within graph collection
		*/
		std::list<Vertex *> *GetAll() const;
		/**
		* Getting list of favorite humans for given adorer within graph collection
		* @param pvFan - adorer
		*/
		std::list<Vertex *> *GetRelations(Vertex *pvFan) const;

		/**
		* Destructor
		*/
		~Graph();
	
	private:
		/// List of humans who are within graph collection
		std::list<Vertex *> m_lVertexes;

		/**
		* Getting number of adorers who are feeling sympathy for this man
		* @pvPippin - adorable man
		*/
		int GetFanCount(Vertex *pvPippin) const;
	};
}