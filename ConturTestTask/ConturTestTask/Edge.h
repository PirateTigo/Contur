/******************************************************************************
* File: Edge.h
* Description: Describes edge like element of graph of relationships
* Created: 06 Mar 2015
* Copyright: (C) PirateTigo
* Author: Artem Tarakanovskiy
* Email: piratetigo@gmail.com

******************************************************************************/

#pragma once

#include "Vertex.h"

namespace relationships
{
	class Vertex;

	/**
	* @class Edge
	* Sympathy from one human to other man
	* @note This class to contain only references
	*/
	class Edge
	{		
	public:
		/**
		* Constructor
		* @param pvBegin - source of sympathy
		* @param pvEnd - object of sympathy
		*/
		Edge(Vertex *pvBegin, Vertex *pvEnd);

		/**
		* Getting of source of sympathy
		*/
		Vertex *GetBegin() const;
		/**
		* Getting of object of sympathy
		*/
		Vertex *GetEnd() const;

		/**
		* Destructor
		*/
		~Edge();

	private:
		/// Source of sympathy
		Vertex *m_pvBegin;
		/// Object of sympathy
		Vertex *m_pvEnd;
	};
}