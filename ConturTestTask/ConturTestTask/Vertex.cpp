#include "stdafx.h"
#include "Vertex.h"

using namespace std;
using namespace relationships;

Vertex::Vertex()
{
	m_pcName = NULL;
	m_iFanCount = 0;
}

Vertex::Vertex(const char *pcName)
{
	m_iFanCount = 0;
	int iSize = strlen(pcName) + 1;
	m_pcName = new char[iSize];
	strcpy_s(m_pcName, iSize, pcName);
}

Vertex::Vertex(const Vertex &rvOther)
{
	int iSize = strlen(rvOther.m_pcName) + 1;
	m_pcName = new char[iSize];
	strcpy_s(m_pcName, iSize, rvOther.m_pcName);
	m_iFanCount = rvOther.m_iFanCount;
}

Vertex& Vertex::operator=(Vertex &rvOther)
{
	Vertex *vResult = static_cast<Vertex *>(new Vertex(rvOther));
	return *vResult;
}

Vertex::iterator Vertex::begin()
{	
	list<Edge *>::iterator iBegin = m_lEdges.begin();
	if (iBegin == m_lEdges.end())
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

Vertex::iterator Vertex::end()
{
	iterator iResult(NULL, this);
	return iResult;
}

char *Vertex::GetName() const
{
	int iSize = strlen(m_pcName) + 1;
	char *pcResult = new char[iSize];
	strcpy_s(pcResult, iSize, m_pcName);
	return pcResult;
}

void Vertex::SetName(const char *pcName)
{
	if (m_pcName != NULL)
	{
		delete[]m_pcName;
		m_pcName = NULL;
	}
	int iSize = strlen(pcName) + 1;
	m_pcName = new char[iSize];
	strcpy_s(m_pcName, iSize, pcName);
}

void Vertex::AddEdge(Edge *peEdge)
{
	m_lEdges.push_back(peEdge);
}

void Vertex::Clear()
{
	if (m_pcName != NULL)
	{
		delete[] m_pcName;
		m_pcName = NULL;
	}

	for each (Edge *peItem in m_lEdges)
		delete peItem;

	m_lEdges.clear();
}

int Vertex::GetFanCount() const
{
	return m_iFanCount;
}

void Vertex::SetFanCount(int iCount)
{
	m_iFanCount = iCount;
}

Vertex::~Vertex()
{
	Clear();	
}

Vertex::iterator::iterator(Edge *peStartPosition, Vertex *pvParent)
{		
	m_plEdges = &pvParent->m_lEdges;
	if (peStartPosition == NULL)
		m_itEdges = m_plEdges->end();
	else
	{
		m_itEdges = m_plEdges->begin();
		while (m_itEdges != m_plEdges->end())
		{
			if (*m_itEdges == peStartPosition)
				break;
			m_itEdges++;
		}
	}
}

Vertex::iterator::iterator(iterator &riOther)
{
	m_itEdges = riOther.m_itEdges;
	m_plEdges = riOther.m_plEdges;
}

Vertex::iterator &Vertex::iterator::operator=(iterator &riOther)
{
	iterator *pitResult = static_cast<iterator *>(new iterator(riOther));
	return *pitResult;
}

Vertex::iterator &Vertex::iterator::operator++()
{
	if (m_itEdges != m_plEdges->end())
		m_itEdges++;
	return *this;
}

bool Vertex::iterator::operator==(iterator &riOther) const
{
	return riOther.m_itEdges == m_itEdges;
}

bool Vertex::iterator::operator!=(iterator &riOther) const
{
	return riOther.m_itEdges != m_itEdges;
}

Edge *Vertex::iterator::operator*() const
{
	return *m_itEdges;
}

Vertex::iterator::~iterator()
{

}