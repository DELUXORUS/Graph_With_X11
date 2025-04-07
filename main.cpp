#include <iostream>
#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>

#include "Graphic.h"
#include "Graph.h"
#include "Vertex.h"
#include "BaseAlgorithm.h"
#include "SimpleChain.h"
#include "EulerianCycle.h"
#include "HamiltonianCycle.h"
#include "WeightGraph.h"
#include "BaseWeightAlgorithm.h"
#include "DijkstraPath.h"
#include "AlgorithmPrima.h"
#include "PrueferEncode.h"
#include "PrueferDecode.h"
#include "PaintAlgorithm.h"
#include "SalemansTask.h"


static int countVertex = 1;
static std::vector<Vertex> selectVertex;

int keyAction(XEvent* event, Graphic& graphic, Graph& graph, WeightGraph& weightGraph) {
    static Algorithm *prueferEncode;
	KeySym symbol;
    Algorithm *simpleChain, *eulerianCycle, *hamiltonianCycle, *paintAlgorithm;
    WeightAlgorithm *dijkstraPath, *algorithmPrima, *salemansTask;

	XLookupString((XKeyEvent*)event, NULL, 0, &symbol, NULL);
	
    switch(symbol) {
  		case XK_q:
            return 1;
  			break;

        case XK_w: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                graph.outputMatrixAdjacency();
                graph.outputListAdjacency();
            }

            break;
        }

        case XK_a: {
            if(weightGraph.getWeightMatrixAdjacency().size() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                weightGraph.outputMatrixWeightGraph();
                weightGraph.outputListWeightGraph();
            }

            break;
        }

        case XK_1: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                simpleChain = new SimpleChain(graph);
                simpleChain->search();
            }

            break;
        }

        case XK_2: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                eulerianCycle = new EulerianCycle(graph);
                eulerianCycle->search();
            }

            break;
        }

        case XK_3: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                hamiltonianCycle = new HamiltonianCycle(graph);
                hamiltonianCycle->search();
            }

            break;
        }

        case XK_4: {
            if(weightGraph.getWeightMatrixAdjacency().size() == 0)
                cout << endl << "The weighted graph is not set!" << endl;
            
            else {
                dijkstraPath = new DijkstraPath(weightGraph);
                dijkstraPath->search();
            }

            break;
        }

        case XK_5: {
            if(weightGraph.getWeightMatrixAdjacency().size() == 0)
                cout << endl << "The weighted graph is not set!" << endl;

            else {
                algorithmPrima = new AlgorithmPrima(weightGraph);
                algorithmPrima->search(); 
                AlgorithmPrima* derivedAlghoritmPrima = static_cast<AlgorithmPrima*>(algorithmPrima);

                if(derivedAlghoritmPrima != nullptr)
                    graphic.rendering(derivedAlghoritmPrima->getTreeListAdjacency(), weightGraph.getVectorVertex());
            }

            break;
        }

        case XK_6: {
            prueferEncode = new PrueferEncode(graph);
            prueferEncode->search();
            break;
        }
        
        case XK_7: {
            if(prueferEncode != nullptr) {
                PrueferEncode* derivedPrueferEncode = static_cast<PrueferEncode*>(prueferEncode);

                if(derivedPrueferEncode != nullptr) {
                    PrueferDecode prueferDecode(derivedPrueferEncode->getCodePruefer());
                    prueferDecode.search();
                }

                else
                    cout << "Failed to cast to PrueferEncode!" << endl;
            }

            else
                cout << endl << "Codify the tree!" << endl;

            break;
        }

        case XK_8: {
            paintAlgorithm = new PaintAlgorithm(graph);
            paintAlgorithm->search();
            break;
        }

        case XK_9: {
            salemansTask = new SalemansTask(weightGraph);
            salemansTask->search();
            break;
        }

        case XK_Escape: {
            graphic.rendering(weightGraph.getWeightListAdjacency(), graph.getVectorVertex());
            break; 
        }

        case XK_BackSpace: {
            graphic.windowCleaning();
            graph.reset();
            weightGraph.reset();
            countVertex = 1;
            selectVertex.clear();
            break;
        }

  		default:
  			break;
	}

	return(0);
}

void dispatch(Graphic& graphic, Graph& graph, WeightGraph& weightGraph) {
    XEvent event;
    int flagDone = 0;

    while(flagDone == 0) {
        XNextEvent(graphic.getDisplay(), &event);
        
        switch(event.type) {
            case ButtonPress: {
                Vertex currentVertex(0, 0, event.xbutton.x, event.xbutton.y);
                
                if (event.xbutton.button == Button1) {       
                    if (graphic.checkCollisionVertex(currentVertex, graph) == true) {
                        if (selectVertex.size() == 0)
                            selectVertex.push_back(currentVertex);

                        else {
                            if (graph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 1 && weightGraph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 0) {
                                cout << endl << "Enter weight for edge " << selectVertex[0].getNumber() << " - " << currentVertex.getNumber() << ":" << endl;
                                int weight;
                                cin >> weight;
                                weightGraph.initializeWeightGraph(graph.getVectorVertex());
                                weightGraph.fillMatrixWeight(selectVertex[0].getNumber(), currentVertex.getNumber(), weight);
                                weightGraph.fillListWeight();
                                graphic.drawWeight(selectVertex[0], currentVertex, weight);
                                selectVertex.clear();
                            }
    
                            else if (graph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 0) {
                                selectVertex.push_back(currentVertex);
                                graph.fillMatrixAdjacency(selectVertex[0].getNumber(), selectVertex[1].getNumber());
                                graph.fillListAdjacency();
                                graphic.drawEdge(selectVertex[0], selectVertex[1]);
                                selectVertex.clear();
                            }
                        }
                    } 
                    
                    else {
                        if (selectVertex.size() == 0) {
                            currentVertex.setNumber(countVertex);
                            graph.getVectorVertex().push_back(currentVertex); 
                            graphic.drawVertex(currentVertex);
                            countVertex++;
                        }
                    }
                }
                break;
            }

            case KeyPress:
                flagDone = keyAction(&event, graphic, graph, weightGraph);
                break;
        }
    }
}

int main(int argc, char **argv) {
    Graph graph;
    WeightGraph weightGraph;
    Graphic graphic;
    graphic.initializeGraphic();
    dispatch(graphic, graph, weightGraph);
}
