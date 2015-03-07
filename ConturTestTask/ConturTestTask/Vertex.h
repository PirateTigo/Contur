/******************************************************************************
* File: Vertex.h
* Description: Describes vertex like element of graph of relationships
* Created: 06 Mar 2015
* Copyright: (C) PirateTigo
* Author: Artem Tarakanovskiy
* Email: piratetigo@gmail.com

******************************************************************************/

#pragma once

#include <list>
#include "Edge.h"

namespace relationships
{
	class Edge;

	/**
	* @class Vertex
	* Human - party relationships
	* @note Human can feel sympathy to other man
	*/
	class Vertex
	{
	public:
		/**
		* @class iterator
		* iterator for Vertex
		*/
		class iterator
		{	
			friend class Vertex;

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
			Edge *operator*() const;

			/**
			* Destructor
			*/
			~iterator();
		
		private:
			/// List of participants bypass
			std::list<Edge *> *m_plEdges;
			/// List iterator
			std::list<Edge *>::iterator m_itEdges;

			/**
			* Hidden constructor
			* @param peStartPosition - start position for bypass
			* @param pvParent - vertex that will be carried out round
			*/
			iterator(Edge *peStartPosition, Vertex *pvParent);
		};		

		/**
		* Empty contsructor
		*/
		Vertex();
		/**
		* Constructor
		* @param pcName - human name
		*/
		Vertex(const char *pcName);
		/**
		* Copy constructor
		* @param rvOther - copy source vertex
		*/
		Vertex(const Vertex &rvOther);

		/**
		* Assignment operator
		* @param rvOther - copy source vertex
		*/
		Vertex &operator=(Vertex &rvOther);

		/**
		* First element of edges collection
		*/
		iterator begin();
		/**
		* Element following the last element of edges collection
		*/
		iterator end();
		
		/**
		* Gettin of name of this human
		*/
		char *GetName() const;
		/**
		* Setting of name for this human
		*/
		void SetName(const char *pcName);
		/**
		* Adding a sympathy for other man
		*/
		void AddEdge(Edge *peEdge);
		/**
		* Clearing all information about this man and his feelings
		*/
		void Clear();
		/**
		* Getting of number of adorers for this man
		* @note Before use it you must set fan count
		*/
		int GetFanCount() const;
		/**
		* Setting of number of adorers
		*/
		void SetFanCount(int iCount);

		/**
		* Destructor
		*/
		~Vertex();

	private:
		/// Name of this human
		char *m_pcName;
		/// Sympathies to other humans
		std::list<Edge *> m_lEdges;
		/// Number of adorers of this man
		int m_iFanCount;
	};
}