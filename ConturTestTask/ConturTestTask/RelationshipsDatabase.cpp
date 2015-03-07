#include "stdafx.h"
#include "RelationshipsDatabase.h"

using namespace std;
using namespace relationships;

RelationshipsDatabase::RelationshipsDatabase()
{
	m_gRelations = NULL;
}

RelationshipsDatabase::RelationshipsDatabase(ifstream &ifNames, ifstream &ifRelationships)
{
	m_gRelations = NULL;
	Load(ifNames, ifRelationships);
}

void RelationshipsDatabase::Load(ifstream &ifNames, ifstream &ifRelationships)
{
	Clear();

	list<Vertex *> lNames;
	list<Edge *> lRelationships;

	char cSimb;
	char *pcName = NULL;
	int iSize = 1;

	// make lNames
	while (ifNames.get(cSimb))
	{
		if (cSimb == '\n' || cSimb == ';')
		{
			if (pcName != NULL)
			{
				Vertex *pvName = static_cast<Vertex *>(new Vertex(pcName));
				lNames.push_back(pvName);
				free(pcName);
				pcName = NULL;
				iSize = 1;
			}
		}
		else
		{
			iSize++;
			pcName = static_cast<char *>(realloc(pcName, iSize));
			pcName[iSize - 2] = cSimb;
			pcName[iSize - 1] = '\0';
		}
	}

	if (pcName != NULL)
	{
		Vertex *pvName = static_cast<Vertex *>(new Vertex(pcName));
		lNames.push_back(pvName);
		free(pcName);
		pcName = NULL;
		iSize = 1;
	}

	// make lRelationships
	bool bFirstLexem = true;
	Vertex *pvBegin = NULL;

	while (ifRelationships.get(cSimb))
	{
		if (cSimb == '\n')
		{
			if (bFirstLexem)
			{
				free(pcName);
				pcName = NULL;
				iSize = 1;
			}
			else
			{
				if (pcName != NULL)
				{
					Vertex *pvEnd = Search(pcName, lNames);
					if (pvEnd != NULL)
					{
						Edge *peRelation = static_cast<Edge *>(new Edge(pvBegin, pvEnd));
						lRelationships.push_back(peRelation);
					}
					free(pcName);
					pcName = NULL;
					iSize = 1;
				}				
				pvBegin = NULL;
				bFirstLexem = true;
			}
		}
		else if (cSimb == ';')
		{
			if (bFirstLexem)
			{
				pvBegin = static_cast<Vertex *>(new Vertex(pcName));
				bFirstLexem = false;
				free(pcName);
				pcName = NULL;
				iSize = 1;
			}
			else
			{
				if (pcName != NULL)
				{
					Vertex *pvEnd = Search(pcName, lNames);
					if (pvEnd != NULL)
					{
						Edge *peRelation = static_cast<Edge *>(new Edge(pvBegin, pvEnd));
						lRelationships.push_back(peRelation);
					}
					free(pcName);
					pcName = NULL;
					iSize = 1;
				}
			}
		}
		else
		{
			iSize++;
			pcName = static_cast<char *>(realloc(pcName, iSize));
			pcName[iSize - 2] = cSimb;
			pcName[iSize - 1] = '\0';
		}
	}

	if (bFirstLexem)
	{
		free(pcName);
		pcName = NULL;
		iSize = 1;
	}
	else
	{
		if (pcName != NULL)
		{
			Vertex *pvEnd = Search(pcName, lNames);
			if (pvEnd != NULL)
			{
				Edge *peRelation = static_cast<Edge *>(new Edge(pvBegin, pvEnd));
				lRelationships.push_back(peRelation);
			}
			free(pcName);
			pcName = NULL;
			iSize = 1;
		}		
		pvBegin = NULL;
	}

	m_gRelations = new Graph(lNames, lRelationships);
}

void RelationshipsDatabase::Clear()
{
	if (m_gRelations != NULL)
		delete m_gRelations;
	m_gRelations = NULL;
}

void RelationshipsDatabase::ShowUnloved(ostream &roOut) const
{
	list<Vertex *> *plUnloved = m_gRelations->GetUnloved();	
	setlocale(LC_ALL, "Russian");
	for each (Vertex *pvItem in *plUnloved)
	{
		char *pcName = pvItem->GetName();		
		roOut << pcName << endl;		
		delete[]pcName;
	}
	setlocale(LC_ALL, "English");
	delete plUnloved;
}

void RelationshipsDatabase::ShowWretched(ostream &roOut) const
{
	list<Vertex *> *plWretched = m_gRelations->GetWretched();	
	setlocale(LC_ALL, "Russian");
	for each (Vertex *pvItem in *plWretched)
	{
		char *pcName = pvItem->GetName();
		roOut << pcName << endl;
		delete[]pcName;
	}
	setlocale(LC_ALL, "English");
	delete plWretched;
}

void RelationshipsDatabase::ShowBeloved(ostream &roOut) const
{
	list<Vertex *> *plBeloved = m_gRelations->GetBeloved();	
	setlocale(LC_ALL, "Russian");
	for each (Vertex *pvItem in *plBeloved)
	{
		char *pcName = pvItem->GetName();
		roOut << pcName << endl;
		delete[]pcName;
	}
	setlocale(LC_ALL, "English");
	delete plBeloved;
}

void RelationshipsDatabase::ShowAll(ostream &roOut) const
{
	list<Vertex *> *plAll = m_gRelations->GetAll();
	setlocale(LC_ALL, "Russian");
	for each (Vertex *pvItem in *plAll)
	{
		char *pcName = pvItem->GetName();
		roOut << pcName << endl;
		delete[]pcName;
	}
	setlocale(LC_ALL, "English");
	delete plAll;
}

void RelationshipsDatabase::ShowRelations(ostream &roOut) const
{
	setlocale(LC_ALL, "Russian");
	for (Graph::iterator iVertex = m_gRelations->begin(); iVertex != m_gRelations->end(); iVertex++)
	{
		char *pcName = (*iVertex)->GetName();
		roOut << pcName << endl;
		delete[]pcName;
		list<Vertex *> *plRelations = m_gRelations->GetRelations(*iVertex);
		if (plRelations->size() > 0)
		{
			for each (Vertex *pvItem in *plRelations)
			{
				char *pcName = pvItem->GetName();
				roOut << "- " << pcName << endl;
				delete[]pcName;
			}
		}
		delete plRelations;
	}
	setlocale(LC_ALL, "English");
}

RelationshipsDatabase::~RelationshipsDatabase()
{
	Clear();
}

Vertex *RelationshipsDatabase::Search(const char *pcName, const list<Vertex *> &rlVertexes) const
{
	for each (Vertex *pvItem in rlVertexes)
	{
		char *pcCurrentName = pvItem->GetName();
		if (strcmp(pcCurrentName, pcName) == 0)
		{
			delete []pcCurrentName;
			return pvItem;
		}
		else
			delete []pcCurrentName;
	}
	return NULL;
}
