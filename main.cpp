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
#include "SalesmansTask.h"
#include "OrientedGraph.h"
#include "DijkstraPathOriented.h"
#include "FloydAlgorithm.h"
#include "FordAlgorithm.h"


static int countVertex = 1;
static std::vector<Vertex> selectVertex;
static std::vector<Vertex> selectVertexForOrientation;

int keyAction(XEvent* event, Graphic& graphic, 
              Graph& graph, WeightGraph& weightGraph, 
              OrientedGraph& orientedGraph) 
{
    static Algorithm *prueferEncode;
	KeySym symbol;
    Algorithm *simpleChain, *eulerianCycle, *hamiltonianCycle, *paintAlgorithm;
    WeightAlgorithm *dijkstraPath, *algorithmPrima, *salesmansTask, *floydAlgorithm, *fordAlgorithm;

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

        case XK_d: {
            if(orientedGraph.getMatrixAdjacency().size() == 0)
                cout << endl << "The graph is not set!" << endl;
            else {
                orientedGraph.outputMatrixAdjacency();
                orientedGraph.outputListAdjacency();
            }

            break;
        }

        case XK_r: {
            if(orientedGraph.getMatrixAdjacency().size() == 0) {
                orientedGraph.testGraph();
                graphic.rendering(orientedGraph.getListAdjacency(), 
                                  orientedGraph.getVectorVertex());
            }
            else {
                cout << endl << "The oriented graph is alredy set!" << endl;
            }
                                
            // graphic.outputInstruction();
            break;
        }

        case XK_1: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;
            else {
                // simpleChain = new SimpleChain(graph);
                simpleChain = new SimpleChain();
                simpleChain->initialize(graph.getListAdjacency(), 
                                          graph.getMatrixAdjacency(), 
                                          graph.getVectorVertex());
                
                simpleChain->search();
            }

            break;
        }

        case XK_2: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;
            else {
                // eulerianCycle = new EulerianCycle(graph);
                eulerianCycle = new EulerianCycle();
                eulerianCycle->initialize(graph.getListAdjacency(), 
                                          graph.getMatrixAdjacency(), 
                                          graph.getVectorVertex());
                eulerianCycle->search();
            }

            break;
        }

        case XK_3: {
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;
            else {
                // hamiltonianCycle = new HamiltonianCycle(graph);
                hamiltonianCycle = new HamiltonianCycle();
                hamiltonianCycle->initialize(graph.getListAdjacency(), 
                                            graph.getMatrixAdjacency(), 
                                            graph.getVectorVertex());
                hamiltonianCycle->search();
            }

            break;
        }

        case XK_4: {
            if (orientedGraph.getMatrixAdjacency().size() == 0) {
                dijkstraPath = new DijkstraPath();

                if (weightGraph.getWeightMatrixAdjacency().size() == 0) {
                    cout << endl << "Neither a weighted nor an oriented graph is defined!" << endl;
                    break;
                }

                dijkstraPath->initialize(weightGraph.getWeightListAdjacency(), 
                                        weightGraph.getWeightMatrixAdjacency(), 
                                        weightGraph.getVectorVertex());
                dijkstraPath->search();
            }
            else {
                dijkstraPath = new DijkstraPathOriented();
                dijkstraPath->initialize(orientedGraph.getListAdjacency(), 
                                        orientedGraph.getMatrixAdjacency(), 
                                        orientedGraph.getVectorVertex());
                dijkstraPath->search();
            }

            break;
        }

        case XK_5: {
            if(weightGraph.getWeightMatrixAdjacency().size() == 0)
                cout << endl << "The weighted graph is not set!" << endl;

            else {
                algorithmPrima = new AlgorithmPrima();
                algorithmPrima->initialize(weightGraph.getWeightListAdjacency(), 
                                           weightGraph.getWeightMatrixAdjacency(), 
                                           weightGraph.getVectorVertex());
                algorithmPrima->search(); 
                AlgorithmPrima* derivedAlghoritmPrima = static_cast<AlgorithmPrima*>(algorithmPrima);

                if(derivedAlghoritmPrima != nullptr)
                    graphic.rendering(derivedAlghoritmPrima->getTreeListAdjacency(), weightGraph.getVectorVertex());
            }

            break;
        }

        case XK_6: {
            if (graph.getNumberVertex() == 0) {
                cout << endl << "The graph is not set!" << endl;
            }
            else {
                // prueferEncode = new PrueferEncode(graph);
                prueferEncode = new PrueferEncode();
                prueferEncode->initialize(graph.getListAdjacency(), 
                                          graph.getMatrixAdjacency(), 
                                          graph.getVectorVertex());
                prueferEncode->search();
            }

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
            if(graph.getNumberVertex() == 0)
                cout << endl << "The graph is not set!" << endl;

            else {
                // paintAlgorithm = new PaintAlgorithm(graph);
                paintAlgorithm = new PaintAlgorithm();
                paintAlgorithm->initialize(graph.getListAdjacency(), 
                                          graph.getMatrixAdjacency(), 
                                          graph.getVectorVertex());
                paintAlgorithm->search();
            }

            break;
        }

        case XK_9: {
            if(weightGraph.getWeightMatrixAdjacency().size() == 0)
                cout << endl << "The weighted graph is not set!" << endl;

            else {
                salesmansTask = new GreedyAlgorithm();
                salesmansTask->initialize(weightGraph.getWeightListAdjacency(), 
                                          weightGraph.getWeightMatrixAdjacency(), 
                                          weightGraph.getVectorVertex());
                salesmansTask->search();
            }

            break;
        }

        case XK_0: {
            if(orientedGraph.getMatrixAdjacency().size() == 0)
                cout << endl << "The oriented graph is not set!" << endl;

            else {
                floydAlgorithm = new FloydAlgorithm();
                floydAlgorithm->initialize(orientedGraph.getListAdjacency(), 
                                          orientedGraph.getMatrixAdjacency(), 
                                          orientedGraph.getVectorVertex());
                floydAlgorithm->search();
            }

            break;
        }

        case XK_F1: {
            if(orientedGraph.getMatrixAdjacency().size() == 0)
                cout << endl << "The oriented graph is not set!" << endl;

            else {
                fordAlgorithm = new FordAlgorithm();
                fordAlgorithm->initialize(orientedGraph.getListAdjacency(), 
                                          orientedGraph.getMatrixAdjacency(), 
                                          orientedGraph.getVectorVertex());
                fordAlgorithm->search();
            }

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

void dispatch(Graphic& graphic, Graph& graph, WeightGraph& weightGraph, OrientedGraph& orientedGraph) {
    XEvent event;
    int flagDone = 0;

    while(flagDone == 0) {
        XNextEvent(graphic.getDisplay(), &event);
        
        switch(event.type) {
            case Expose: {
                graphic.windowCleaning();
                graphic.rendering(weightGraph.getWeightListAdjacency(), weightGraph.getVectorVertex());
                break;
            }

            case ButtonPress: {
                Vertex currentVertex(0, 0, event.xbutton.x, event.xbutton.y);
                
                if (event.xbutton.button == Button1) {       
                    if (graphic.checkCollisionVertex(currentVertex, graph.getVectorVertex()) == true) {
                        if (selectVertex.size() == 0)
                            selectVertex.push_back(currentVertex);
                        else {
                            if (graph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 1 && 
                                weightGraph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 0) 
                            {
                                cout << endl << "Enter weight for edge " << selectVertex[0].getNumber() << " - " << currentVertex.getNumber() << ":" << endl;
                                int weight;
                                cin >> weight;
                                graphic.drawWeight(selectVertex[0], currentVertex, weight);
                                weightGraph.getVectorVertex() = graph.getVectorVertex();
                                weightGraph.fillMatrixWeight(selectVertex[0].getNumber(), currentVertex.getNumber(), weight);
                                weightGraph.fillListWeight();

                                if (orientedGraph.getMatrixAdjacency().size() != 0) {
                                    if (orientedGraph.checkEdge(selectVertex[0].getNumber(), currentVertex.getNumber()) == 1) {
                                        orientedGraph.fillMatrixAdjacency(selectVertex[0].getNumber(), currentVertex.getNumber(), weight);
                                    }
                                    else {
                                        orientedGraph.fillMatrixAdjacency(currentVertex.getNumber(), selectVertex[0].getNumber(), weight);
                                    }

                                    orientedGraph.fillListAdjacency();
                                }

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

                if (event.xbutton.button == Button3) {
                    if (graphic.checkCollisionVertex(currentVertex, graph.getVectorVertex()) == true) {
                        if (selectVertexForOrientation.size() == 0) {
                            selectVertexForOrientation.push_back(currentVertex);
                        }
                        else {
                            if (graph.checkEdge(selectVertexForOrientation[0].getNumber(), currentVertex.getNumber()) == 1) {

                                Vertex initialVertex = selectVertexForOrientation[0];
                                Vertex finalVertex = currentVertex;
                                graphic.drawArrow(initialVertex, finalVertex);
                                
                                int weight;
                                
                                if (weightGraph.checkEdge(selectVertexForOrientation[0].getNumber(), currentVertex.getNumber()) == 1) {
                                    weight = weightGraph.getWeightMatrixAdjacency()[initialVertex.getNumber() - 1][finalVertex.getNumber() - 1];
                                    graphic.drawWeight(initialVertex, finalVertex, weight);
                                }
                                else {
                                    weight = 1;
                                }
                                
                                orientedGraph.getVectorVertex() = graph.getVectorVertex();
                                orientedGraph.fillMatrixAdjacency(initialVertex.getNumber(), finalVertex.getNumber(), weight);
                                orientedGraph.fillListAdjacency();
                                selectVertexForOrientation.clear();
                            }
                        }
                    }
                }

                break;
            }

            case KeyPress:
                flagDone = keyAction(&event, graphic, graph, weightGraph, orientedGraph);
                break;
        }
    }
}

int main(int argc, char **argv) {
    Graph graph;
    WeightGraph weightGraph;
    OrientedGraph orientedGraph;
    Graphic graphic;
    graphic.initializeGraphic();
    dispatch(graphic, graph, weightGraph, orientedGraph);
}
