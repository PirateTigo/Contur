#include "stdafx.h"
#include "Graph.h"

using namespace std;
using namespace relationships;

Graph::Graph(list<Vertex *> &rlVertexes, list<Edge *> &rlEdges)
{
	for each(Vertex *pvItem in rlVertexes)
	{
		list<Edge *> lBeRemoved;
		char *pcVertexName = pvItem->GetName();
		for each (Edge *peItem in rlEdges)
		{			
			char *pcEdgeBeginName = peItem->GetBegin()->GetName();
			if (strcmp(pcVertexName, pcEdgeBeginName) == 0)
			{
				pvItem->AddEdge(peItem);
				lBeRemoved.push_back(peItem);
			}			
			delete []pcEdgeBeginName;			
		}

		delete[]pcVertexName;

		for each (Edge *peItem in lBeRemoved)		
			rlEdges.remove(peItem);		
	}

	for each (Vertex *pvItem in rlVertexes)
		m_lVertexes.push_back(pvItem);
}

Graph::iterator Graph::begin()
{
	list<Vertex *>::iterator iBegin = m_lVertexes.begin();
	if (iBegin == m_lVertexes.end())
	{
		iterator iResult(NULL, this);
		return iResult;
	}
	else
	{
		iterator iResult(*iBegin, this);
		return iResult;
	}
}

Graph::iterator Graph::end()
{
	iterator iResult(NULL, this);
	return iResult;
}

list<Vertex *> *Graph::GetUnloved() const
{
	list<Vertex *> *plResult = static_cast<list<Vertex *> *>(new list<Vertex *>());	
	for each(Vertex *pvItem in m_lVertexes)
	{		
		bool bLoved = false;
		for each (Vertex *pvExpectedFan in m_lVertexes)
		{
			if (pvItem == pvExpectedFan) continue;			
			for (Vertex::iterator iEdge = pvExpectedFan->begin(); iEdge != pvExpectedFan->end(); iEdge++)
			{
				if ((*iEdge)->GetEnd() == pvItem)
				{
					bLoved = true;
					break;
				}
			}

			if (bLoved)
				break;
		}

		if (!bLoved)
			plResult->push_back(pvItem);
	}
	return plResult;
}

list<Vertex *> *Graph::GetWretched() const
{
	list<Vertex *> *plResult = static_cast<list<Vertex *> *>(new list<Vertex *>());
	for each (Vertex *pvItem in m_lVertexes)
	{
		bool bWretched = true;
		for (Vertex::iterator iLikeQuery = pvItem->begin(); iLikeQuery != pvItem->end(); iLikeQuery++)
		{
			Vertex *pvFavourite = (*iLikeQuery)->GetEnd();
			for (Vertex::iterator iLikeAnswer = pvFavourite->begin();
				iLikeAnswer != pvFavourite->end(); iLikeAnswer++)
			{
				if ((*iLikeAnswer)->GetEnd() == pvItem)
				{
					bWretched = false;
					break;
				}
			}

			if (!bWretched)
				break;
		}
		
		if (bWretched)		
			if (pvItem->begin() != pvItem->end())
				plResult->push_back(pvItem);		
	}
	return plResult;
}

list<Vertex *> *Graph::GetBeloved() const
{
	list<Vertex *> *plResult = static_cast<list<Vertex *> *>(new list<Vertex *>());

	int iMaxFanCount = 0;

	for each (Vertex *pvItem in m_lVertexes)
	{
		int iFanCount = GetFanCount(pvItem);
		pvItem->SetFanCount(iFanCount);
		if (iFanCount > iMaxFanCount)
			iMaxFanCount = iFanCount;
	}
	
	for each (Vertex *pvItem in m_lVertexes)
		if (pvItem->GetFanCount() == iMaxFanCount)
			plResult->push_back(pvItem);

	return plResult;
}

list<Vertex *> *Graph::GetAll() const
{
	list<Vertex *> *plResult = static_cast<list<Vertex *> *>(new list<Vertex *>());

	for each (Vertex *pvItem in m_lVertexes)
		plResult->push_back(pvItem);	

	return plResult;
}

list<Vertex *> *Graph::GetRelations(Vertex *pvFan) const
{
	list<Vertex *> *plResult = static_cast<list<Vertex *> *>(new list<Vertex *>());

	for (Vertex::iterator iLikeQuery = pvFan->begin(); iLikeQuery != pvFan->end(); iLikeQuery++)
		plResult->push_back((*iLikeQuery)->GetEnd());

	return plResult;
}

Graph::~Graph()
{
	for each (Vertex *pvItem in m_lVertexes)
		delete pvItem;

	m_lVertexes.clear();
}

int Graph::GetFanCount(Vertex *pvPippin) const
{
	int count = 0;
	for (Vertex::iterator iLikeQuery = pvPippin->begin(); iLikeQuery != pvPippin->end(); iLikeQuery++)
	{
		Vertex *pvFavourite = (*iLikeQuery)->GetEnd();
		for (Vertex::iterator iLikeAnswer = pvFavourite->begin();
			iLikeAnswer != pvFavourite->end(); iLikeAnswer++)
		{
			if ((*iLikeAnswer)->GetEnd() == pvPippin)
				count++;
		}
	}
	return count;
}

Graph::iterator::iterator(Vertex *pvStartPosition, Graph *pgParent)
{
	m_plVertexes = &pgParent->m_lVertexes;
	if (pvStartPosition == NULL)
		m_itVertexes = m_plVertexes->end();
	else
	{
		m_itVertexes = m_plVertexes->begin();
		while (m_itVertexes != m_plVertexes->end())
		{
			if (*m_itVertexes == pvStartPosition)
				break;
			m_itVertexes++;
		}
	}
}

Graph::iterator::iterator(iterator &riOther)
{
	m_itVertexes = riOther.m_itVertexes;
	m_plVertexes = riOther.m_plVertexes;
}

Graph::iterator &Graph::iterator::operator=(iterator &riOther)
{
	iterator *pitResult = static_cast<iterator *>(new iterator(riOther));
	return *pitResult;
}

Graph::iterator &Graph::iterator::operator++()
{
	if (m_itVertexes != m_plVertexes->end())
		m_itVertexes++;
	return *this;
}

bool Graph::iterator::operator==(iterator &riOther) const
{
	return m_itVertexes == riOther.m_itVertexes;
}

bool Graph::iterator::operator!=(iterator &riOther) const
{
	return m_itVertexes != riOther.m_itVertexes;
}

Vertex *Graph::iterator::operator*() const
{
	return *m_itVertexes;
}

Graph::iterator::~iterator()
{
}