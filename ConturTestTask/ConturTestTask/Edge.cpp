#include "stdafx.h"
#include "Edge.h"

using namespace relationships;

Edge::Edge(Vertex *pvBegin, Vertex *pvEnd)
{
	m_pvBegin = pvBegin;
	m_pvEnd = pvEnd;
}

Vertex *Edge::GetBegin() const
{
	return m_pvBegin;
}

Vertex *Edge::GetEnd() const
{
	return m_pvEnd;
}

Edge::~Edge()
{	
}
