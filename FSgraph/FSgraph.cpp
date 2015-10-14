//Author: Nicolas Silveira Kagami
//Slightly different than T1's 
//Adding findEdge and Reflexive edges with cost (which means capacity now) 0
//New constructor just for T4
#include "FSgraph.h"


FSgraph::FSgraph(unsigned vertNum, unsigned edgeNum)
{
    numEdges = edgeNum;
    numVerts = vertNum;
    currentEdge = 0;
    currentVert = 0;
    edges = (EDGE*) malloc(sizeof(EDGE)*edgeNum);
    vertices = (VERT*) malloc(sizeof(VERT)*vertNum);
}
/*
FSgraph::FSgraph(std::istream& in)
{
    std::string line="", dummy;
    unsigned n,m;

    while (line.substr(0,5) != "p max")
    {
        getline(in,line);
    }
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> n >> m;

    //Init
    numVerts = n;
    numEdges = 2*m;
    currentEdge = 0;
    currentVert = 0;
    edges = (EDGE*) malloc(sizeof(EDGE)*numEdges);
    vertices = (VERT*) malloc(sizeof(VERT)*numVerts);
    unsigned i =0;
    for(i=0;i<numVerts;i++)
    {
        vertices[i].edgeNum=0;
        vertices[i].index=0;
    }
    source=0;
    target=0;

    std::stringstream buffer;
    buffer << in.rdbuf();
    i=0;
    while (i<m)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        if (line.substr(0,2) == "a ") 
        {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            preallocate(u,v);
            preallocate(v,u);//Added for T3 Advanced algs
            i++;
        }
        if (line.substr(0,2) == "n ") 
        {
            std::stringstream arc(line);
            unsigned u;
            char ac,n;
            arc >> ac >> u >> n;
            if(n == 's')
                source = u;
            if(n == 't')
                target = u;
        }
    }
    indexify();
    buffer.seekg(0);
    i=0;
    while (i<m)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        if (line.substr(0,2) == "a ") 
        {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            proposeEdge(u,v,w);
            proposeEdge(v,u,0);
            i++;
        }
    }

}
*/
FSgraph::FSgraph(std::istream& in)
{
    std::string line="", dummy;
    getline(in,line);
    
    std::stringstream linestr;
    linestr.str(line);
    linestr >> w >> h;

    //Init
    numVerts = w*h + 2;
    numEdges = 2*(h-1)*(3*w-2) + w*h;
    currentEdge = 0;
    currentVert = 0;
    edges = (EDGE*) malloc(sizeof(EDGE)*numEdges);
    vertices = (VERT*) malloc(sizeof(VERT)*numVerts);

    unsigned i =0,j=0;
    maxCapacity = 0;

    for(i=0;i<numVerts;i++)
    {
        vertices[i].edgeNum=0;
        vertices[i].index=0;
    }
    source=numVerts - 1;
    target=numVerts;

    std::stringstream buffer;
    buffer << in.rdbuf();
    for(i=0;i<h;i++)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        std::stringstream arc(line);
        int weight;
        unsigned u,v;
        for(j=0;j<w;j++)
        {
            u=i*w+j;
            arc >> weight;
            if(weight>0)
            {
                maxCapacity += weight;
                preallocate(source,u+1);
            }
            else
            {
                maxCapacity -= weight; //??
                preallocate(u+1,target);
            }
            if(i<(h-1))
            {
                v=u+w;
                if(j!=0)
                {
                    preallocate(u+1,v);
                    preallocate(v,u+1);
                }
                preallocate(u+1,v+1);
                preallocate(v+1,u+1);
                if(j!= (w-1))
                {
                    preallocate(u+1,v+2);
                    preallocate(v+2,u+1);
                }
            }
        }
    }
    indexify();
    buffer.seekg(0);
    i=0;
    for(i=0;i<h;i++)
    {
        if(!std::getline(buffer, line))
        {
            printf("Parsing Error\n");
            exit(1);
        }
        std::stringstream arc(line);
        int weight;
        unsigned u,v;
        for(j=0;j<w;j++)
        {
            arc >> weight;
            u=i*w+j;
            if(weight>0)
            {
                proposeEdge(source,u+1,weight);
            }
            else
            {
                proposeEdge(u+1,target,-weight);
            }

            if(i<(h-1))
            {
                v=u+w;
                if(j!= 0)
                {
                    proposeEdge(u+1,v,0);
                    proposeEdge(v,u+1,maxCapacity);
                }
                proposeEdge(u+1,v+1,0);
                proposeEdge(v+1,u+1,maxCapacity);
                if(j!= (w-1))
                {
                    proposeEdge(u+1,v+2,0);
                    proposeEdge(v+2,u+1,maxCapacity);
                }
            }
        }
    }

}
FSgraph::~FSgraph()
{
    free(edges);
    free(vertices);
}
void FSgraph::preallocate(unsigned vert, unsigned tgt)
{
    if(vert>numVerts)
    {
        printf("Invalid vertex\n");
        exit(1);
    }
    vertices[vert-1].edgeNum++;
}
void FSgraph::indexify()
{
    for(unsigned i = 0; i<(numVerts-1);i++)
    {
        vertices[i+1].index = vertices[i].index + vertices[i].edgeNum;
        vertices[i].edgeNum =0;
    }
    vertices[numVerts-1].edgeNum=0;
}
void FSgraph::addEdge(unsigned vert,unsigned tgt,unsigned wht)
{
    //printf("Adding Edge %d %d %d\n",vert, tgt, wht);
    if(vert>numVerts)
    {
        printf("Invalid vertex\n");
        exit(1);
    }
    unsigned ind = vertices[vert-1].index + vertices[vert-1].edgeNum;
    if(ind>numEdges)
    {
        printf("Invalid Edge\n");
        exit(1);
    }
    edges[ind].target = tgt;    
    edges[ind].weight = wht;
    edges[ind].residual = wht;

    vertices[vert-1].edgeNum++;
}
void FSgraph::proposeEdge(unsigned vert, unsigned tgt,unsigned wht)
{
   unsigned i,j;
   for(i=vertices[vert-1].index,j=0;j<vertices[vert-1].edgeNum;j++)
   {
        if(edges[i+j].target == tgt)
        {
            //It already exists, let the bigger prevail
            if(wht>edges[i+j].weight) 
            {
                edges[i+j].weight = wht;
                edges[i+j].residual = wht;
            }
            return;
        }
   }
   addEdge(vert,tgt,wht);
}
unsigned FSgraph::findEdge(unsigned u, unsigned v)
{
   unsigned i,j;
   for(i=vertices[u-1].index,j=0;j<vertices[u-1].edgeNum;j++)
   {
        if(edges[i+j].target == v)
            return i+j;
   }
   return 0;
}
void FSgraph::print()
{
    printf("Forward Star Graph\n");
    printf("MaxCapacity: %d\n",maxCapacity);
    printf("Vertices: %d\n",numVerts);
    printf("Edges: %d\n",numEdges);
    for(unsigned i = 0;i<numVerts;i++)
    {
        printf("Vert %d",i+1);
        for(unsigned b = vertices[i].index,j=0;j<vertices[i].edgeNum;j++)
        {
            printf("\t %d %d/%d",edges[b+j].target,edges[b+j].residual,edges[b+j].weight);
        }
        printf("\n");
    }
}
void FSgraph::printT4()
{
    printf("Forward Star Graph\n");
    printf("MaxCapacity: %d\n",maxCapacity);
    printf("Vertices: %d\n",numVerts);
    printf("Edges: %d\n",numEdges);
    unsigned u, edge;
    for(unsigned i=0;i<h;i++)
    {
        for(unsigned j=0;j<w;j++)
        {
            u=i*w+j;
            edge=findEdge(u+1,target);

            if(edge == 0)
            {
                edge=findEdge(source,u+1);
                printf("+");
                if(edge != 0 && edges[edge-1].residual < edges[edge-1].weight)
                    printf("1 ");
                else
                    printf("0 ");
            }
            else
            {
                printf("-");
                if(edge != 0 && edges[edge-1].residual == edges[edge-1].weight)
                    printf("1 ");
                else
                    printf("0 ");
            }
        }
        printf("\n");
    }
}
void FSgraph::printT4b()
{
    printf("Forward Star Graph\n");
    printf("MaxCapacity: %d\n",maxCapacity);
    printf("Vertices: %d\n",numVerts);
    printf("Edges: %d\n",numEdges);
    unsigned u, edge;
    opm = (bool*) malloc(sizeof(bool)*w*h + 2);
    for(unsigned i=0;i<w*h;i++)
        opm[i] = false;

    

    std::stack<unsigned> st;
    st.push(source);

    opm[source-1] = true;

    while(!st.empty())
    {
        unsigned p = st.top();
        st.pop();
        if(p == target) 
        {
            break;
        }
        for(unsigned b=vertices[p-1].index,i=0;i<vertices[p-1].edgeNum;i++)
        {
            unsigned neighbor = edges[b+i].target;
            unsigned wht = edges[b+i].residual;
            if((!opm[neighbor-1])&&(wht>0))
            {
                opm[neighbor-1] = true;
                st.push(neighbor);
            }
        }
    }

    for(unsigned i=0;i<h;i++)
    {
        for(unsigned j=0;j<w;j++)
            if(opm[i*w+j])
                printf("1");
            else
                printf("0");
        printf("\n");
    }
}
