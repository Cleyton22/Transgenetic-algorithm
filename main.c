#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>




typedef struct {
    int identification;
    double coordinateX;
    double coordinateY;
    int profit;
} Vertice;




typedef struct {
    Vertice *vertices;
    int amountVertices;
    double travelCost;
    double totalLatency;
    int totalProfit;
    int depotPosition;
} Solution;




typedef struct {
    int identification;
    double coordinateX;
    double coordinateY;
    int profit;
    double key;
    int parentVertice;
} VerticeTree;




typedef struct {
    Solution *solutions;
    int amountSolutions;
} PosterioriInformation;




typedef struct NodeVertice {
    Vertice vertice;
    struct NodeVertice *next;
} NodeVertice;




typedef struct {
    NodeVertice *head;
    int size;
} ListVertice;




typedef struct NodeSolution {
    Solution *solution;
    struct NodeSolution *next;
} NodeSolution;




typedef struct {
    NodeSolution *head;
    int size;
} ListSolution;




typedef struct NodeVerticeTree {
    VerticeTree *verticeTree;
    struct NodeVerticeTree *next;
} NodeVerticeTree;




typedef struct {
    NodeVerticeTree *head;
    int size;
} ListVerticeTree;




ListVertice *createListVertice() {
    ListVertice *list = malloc(sizeof(ListVertice));
    list->head = NULL;
    list->size = 0;
    return list;
}




NodeVertice* addToListVertice(ListVertice *list, Vertice vertice, NodeVertice *lastNode) {
    NodeVertice *node = malloc(sizeof(NodeVertice));
    node->vertice = vertice;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        lastNode->next = node;
    }

    list->size++;
    return node;
}




void removeFromListVertice(ListVertice *list, Vertice vertice) {
    NodeVertice *current = list->head;
    NodeVertice *previous = NULL;

    while (current != NULL && current->vertice.identification != vertice.identification) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    list->size--;
}




int isListVerticeEmpty(ListVertice *list) {
    return list->size == 0;
}




ListSolution *createListSolution() {
    ListSolution *list = malloc(sizeof(ListSolution));
    list->head = NULL;
    list->size = 0;
    return list;
}




NodeSolution* addToListSolution(ListSolution *list, Solution *solution, NodeSolution *lastNode) {
    NodeSolution *node = malloc(sizeof(NodeSolution));
    node->solution = solution;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        lastNode->next = node;
    }

    list->size++;
    return node;
}




void removeFromListSolution(ListSolution *list, Solution *solution) {
    NodeSolution *current = list->head;
    NodeSolution *previous = NULL;

    while (current != NULL && current->solution != solution) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    list->size--;
}




int isListSolutionEmpty(ListSolution *list) {
    return list->size == 0;
}




ListVerticeTree *createListVerticeTree() {
    ListVerticeTree *list = malloc(sizeof(ListVerticeTree));
    list->head = NULL;
    list->size = 0;
    return list;
}




NodeVerticeTree* addToListListVerticeTree(ListVerticeTree *list, VerticeTree *verticeTree, NodeVerticeTree *lastNode) {
    NodeVerticeTree *node = malloc(sizeof(NodeVerticeTree));
    node->verticeTree = verticeTree;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        lastNode->next = node;
    }

    list->size++;
    return node;
}




void removeFromListVerticeTree(ListVerticeTree *list, VerticeTree *verticeTree) {
    NodeVerticeTree *current = list->head;
    NodeVerticeTree *previous = NULL;

    while (current != NULL && current->verticeTree->identification != verticeTree->identification) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    list->size--;
}




int isListVerticeTreeEmpty(ListVerticeTree *list) {
    return list->size == 0;
}




void printInstanceData(Vertice *allVertices, int numVertices) {
    printf("Instancia completa:\n\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d %.1lf %.1lf %d\n", allVertices[i].identification, allVertices[i].coordinateX, allVertices[i].coordinateY, allVertices[i].profit);
    }
}




void printVertice(Vertice vertice){
    printf("Vertice %d\n", vertice.identification);
    printf("Posicao: X %.2lf Y %.2lf\n", vertice.coordinateX, vertice.coordinateY);
    printf("Lucro: %d\n\n", vertice.profit);
}




void printListVertice(ListVertice *list){
    for (NodeVertice *node = list->head; node != NULL; node = node->next) {
        printVertice(node->vertice);
    }
}




void printSolution(Solution *solution) {
    for (int i = 0; i < solution->amountVertices; i++) {
        printf("Vertice %d %.2lf %.2lf %d\n", solution->vertices[i].identification, solution->vertices[i].coordinateX, solution->vertices[i].coordinateY, solution->vertices[i].profit);
    }
    printf("\nCusto total: %.2lf\n", solution->travelCost);
    printf("Latencia total: %.2lf\n", solution->totalLatency);
    printf("Lucro total: %d\n", solution->totalProfit);
    printf("Quantidade de clientes atendidos: %d\n", solution->amountVertices - 1);
    printf("Posicao do deposito: %d\n", solution->depotPosition);
    printf("\n");
}




void printVerticeTree(VerticeTree *verticeTree){
    printf("Vertice %d\n", verticeTree->identification);
    printf("Posicao: X %.2lf Y %.2lf\n", verticeTree->coordinateX, verticeTree->coordinateY);
    printf("Lucro: %d\n\n", verticeTree->profit);
    printf("Menor peso atual: %.2lf\n", verticeTree->key);
    printf("Vertice para o menor peso atual: %d\n\n", verticeTree->parentVertice);
}




void printListVerticeTree(ListVerticeTree *listTree){
    for (NodeVerticeTree *node = listTree->head; node != NULL; node = node->next) {
        printVerticeTree(node->verticeTree);
    }
}




double verticesDistanceCalculator(Vertice verticeA, Vertice verticeB){
    double distanceAB = sqrt((verticeA.coordinateX - verticeB.coordinateX) * (verticeA.coordinateX - verticeB.coordinateX) + (verticeA.coordinateY - verticeB.coordinateY) * (verticeA.coordinateY - verticeB.coordinateY));

    return distanceAB;
}




void solutionTotalTravelCostAndProfit(Solution *solution){
    for (int i = 0; i < (solution->amountVertices); i ++){
        if (solution->amountVertices != (i+1)){
            solution->travelCost += verticesDistanceCalculator(solution->vertices[i], solution->vertices[i + 1]);
            solution->totalProfit += solution->vertices[i].profit;
        } else{
            solution->travelCost += verticesDistanceCalculator(solution->vertices[i], solution->vertices[0]);
            solution->totalProfit += solution->vertices[i].profit;
        }
    }
}




void sumOrSubtractVerticeLatency(Solution *solution, int verticePosition, int adjacentPosition, int option){
    if (solution->depotPosition == 0){
        switch (option){
        case 1:
            //Subtrair usando o anterior
            solution->totalLatency -= (((solution->amountVertices - 1) - (verticePosition - 1)) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
            break;
        case 2:
            //Subtrair usando o próximo
            solution->totalLatency -= (((solution->amountVertices - 1) - (adjacentPosition - 1)) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
            break;
        case 3:
            //Somar usando o anterior
            solution->totalLatency += (((solution->amountVertices - 1) - (verticePosition - 1)) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
            break;
        case 4:
            //Somar usando o próximo
            solution->totalLatency += (((solution->amountVertices - 1) - (adjacentPosition - 1)) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
            break;
        default:
            break;
        }
    } else {
        if (verticePosition < solution->depotPosition) {
            switch (option){
            case 1:
                //Subtrair usando o anterior
                solution->totalLatency -= ((solution->depotPosition - verticePosition) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
                break;
            case 2:
                //Subtrair usando o próximo
                solution->totalLatency -= ((solution->depotPosition - adjacentPosition) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                break;
            case 3:
                //Somar usando o anterior
                solution->totalLatency += ((solution->depotPosition - verticePosition) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
                break;
            case 4:
                //Somar usando o próximo
                solution->totalLatency += ((solution->depotPosition - adjacentPosition) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                break;
            default:
                break;
            }
        } else{
            switch (option){
            case 1:
                //Subtrair usando o anterior
                solution->totalLatency -= ((solution->depotPosition + (solution->amountVertices - verticePosition)) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
                break;
            case 2:
                //Subtrair usando o próximo
                if (adjacentPosition != 0){
                    solution->totalLatency -= ((solution->depotPosition + (solution->amountVertices - adjacentPosition)) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                } else {
                    solution->totalLatency -= (solution->depotPosition * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                }
                break;
            case 3:
                //Somar usando o anterior
                solution->totalLatency += ((solution->depotPosition + (solution->amountVertices - verticePosition)) * verticesDistanceCalculator(solution->vertices[adjacentPosition], solution->vertices[verticePosition]));
                break;
            case 4:
                //Somar usando o próximo
                if (adjacentPosition != 0){
                    solution->totalLatency += ((solution->depotPosition + (solution->amountVertices - adjacentPosition)) * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                } else {
                    solution->totalLatency += (solution->depotPosition * verticesDistanceCalculator(solution->vertices[verticePosition], solution->vertices[adjacentPosition]));
                }
                break;
            default:
                break;
            }
        }
    }
}




void solutionTotalLatency(Solution *solution){
    for (int i = 0; i < solution->amountVertices; i++){
        if (solution->vertices[i].identification == 1){
            solution->depotPosition = i;
            break;
        }
    }

    for (int i = 0; i < solution->amountVertices; i++){
        if (i != solution->depotPosition){
            if ((i - 1) == -1){
                sumOrSubtractVerticeLatency(solution, i, solution->amountVertices - 1, 3);
            }else{
                sumOrSubtractVerticeLatency(solution, i, i - 1, 3);
            }
        }
    }
}




int dominance(Solution *solutionA, Solution *solutionB){
    if (solutionA->travelCost <= solutionB->travelCost && solutionA->totalLatency < solutionB->totalLatency && solutionA->totalProfit >= solutionB->totalProfit){
        return 1;
    } else if(solutionA->travelCost < solutionB->travelCost && solutionA->totalLatency <= solutionB->totalLatency && solutionA->totalProfit >= solutionB->totalProfit){
        return 1;
    } else if(solutionA->travelCost <= solutionB->travelCost && solutionA->totalLatency <= solutionB->totalLatency && solutionA->totalProfit > solutionB->totalProfit){
        return 1;
    } else{
        return 0;
    }
}




Solution* copySolution(Solution *originalSolution){
    Solution *copiedSolution = malloc(sizeof(Solution));
    copiedSolution->amountVertices = originalSolution->amountVertices;
    copiedSolution->totalProfit = originalSolution->totalProfit;
    copiedSolution->travelCost = originalSolution->travelCost;
    copiedSolution->totalLatency = originalSolution->totalLatency;
    copiedSolution->depotPosition = originalSolution->depotPosition;

    copiedSolution->vertices = malloc((copiedSolution->amountVertices) * sizeof(Vertice));

    for (int i = 0; i < copiedSolution->amountVertices; i++){
        copiedSolution->vertices[i] = originalSolution->vertices[i];
    }

    return copiedSolution;
}




Solution copySolutionWithoutPointer(Solution *originalSolution, int option){
    Solution copiedSolution;
    copiedSolution.amountVertices = originalSolution->amountVertices;
    copiedSolution.totalProfit = originalSolution->totalProfit;
    copiedSolution.totalLatency = originalSolution->totalLatency;
    copiedSolution.depotPosition = originalSolution->depotPosition;

    copiedSolution.vertices = malloc((copiedSolution.amountVertices) * sizeof(Vertice));

    for (int i = 0; i < copiedSolution.amountVertices; i++){
        copiedSolution.vertices[i] = originalSolution->vertices[i];
    }

    if (option == 1){
        copiedSolution.travelCost = originalSolution->travelCost + verticesDistanceCalculator(copiedSolution.vertices[copiedSolution.amountVertices - 1], copiedSolution.vertices[0]);
    } else{
        copiedSolution.travelCost = originalSolution->travelCost;
    }

    return copiedSolution;
}




void onlyAddNonDominatedSolutions(ListSolution *allNonDominatedSolutions, Solution *candidateSolution){
    if(isListSolutionEmpty(allNonDominatedSolutions)){
        Solution *newSolution = copySolution(candidateSolution);
        NodeSolution *lastNode = NULL;
        lastNode = addToListSolution(allNonDominatedSolutions, newSolution, lastNode);
    } else{
        int proceed = 0;

        for (NodeSolution *current = allNonDominatedSolutions->head; current != NULL; current = current->next) {
            if(dominance(current->solution, candidateSolution) == 1 || (current->solution->totalLatency == candidateSolution->totalLatency && current->solution->travelCost == candidateSolution->travelCost && current->solution->totalProfit == candidateSolution->totalProfit)){
                proceed = 1;
                break;
            }

            if(current->next == NULL){
                Solution *newSolution = copySolution(candidateSolution);
                NodeSolution *newNode = malloc(sizeof(NodeSolution));
                newNode->solution = newSolution;
                newNode->next = NULL;
                current->next = newNode;
                allNonDominatedSolutions->size++;
                break;
            }
        }

        if(proceed == 0){
            NodeSolution *current2 = allNonDominatedSolutions->head;
            NodeSolution *previous2 = NULL;

            while (current2 != NULL) {
                NodeSolution *nextNode = current2->next;
                if((dominance(candidateSolution, current2->solution) == 1)){
                    if(previous2 == NULL){
                        allNonDominatedSolutions->head = current2->next;
                    }else{
                        previous2->next = current2->next;
                    }
                    free(current2->solution->vertices);
                    free(current2->solution);
                    free(current2);
                    allNonDominatedSolutions->size--;
                } else {
                    previous2 = current2;
                }
                current2 = nextNode;
            }
        }
    }
}




Solution* paretoFrontInitialAproximationConstructor(int numVertices, Vertice *allVertices, double alpha){
    Solution *paretoFrontIA = malloc((numVertices - 1) * sizeof(Solution));

    int currentPFIASolution = 0;

    Solution *solution = malloc(sizeof(Solution));
    solution->travelCost = 0;
    solution->totalLatency = 0;
    solution->totalProfit = 0;
    solution->vertices = malloc(numVertices * sizeof(Vertice));
    solution->vertices[0] = allVertices[0];
    solution->amountVertices = 1;
    solution->depotPosition = 0;

    ListVertice *candidatesList = createListVertice();

    NodeVertice *lastNode = NULL;

    for (int i = 1; i < numVertices; i++) {
        lastNode = addToListVertice(candidatesList, allVertices[i], lastNode);
    }

    while (candidatesList->size > 0){
        double gmin = DBL_MAX;
        double gmax = DBL_MIN;

        for (NodeVertice *node = candidatesList->head; node != NULL; node = node->next){
            double cost = verticesDistanceCalculator(solution->vertices[solution->amountVertices - 1], node->vertice);

            double g = cost / node->vertice.profit;

            if(g < gmin){
                gmin = g;
            }
            if(g > gmax){
                gmax = g;
            }
        }

        double threshold = gmin + alpha * (gmax - gmin);

        Vertice *restrictedCandidatesList = malloc((numVertices - solution->amountVertices) * sizeof(Vertice));

        int sizeRCL = 0;

        for (NodeVertice *node = candidatesList->head; node != NULL; node = node->next){
            double cost = verticesDistanceCalculator(solution->vertices[solution->amountVertices - 1], node->vertice);

            double g = cost / node->vertice.profit;

            if(g <= threshold){
                restrictedCandidatesList[sizeRCL] = node->vertice;

                sizeRCL++;
            }
        }

        int randomIndex = rand() % sizeRCL;

        Vertice selectedVertice = restrictedCandidatesList[randomIndex];

        solution->vertices[solution->amountVertices] = selectedVertice;
        solution->travelCost += verticesDistanceCalculator(solution->vertices[solution->amountVertices - 1], selectedVertice);
        solution->totalProfit += selectedVertice.profit;
        solution->amountVertices++;

        double latency = 0;

        for (int i = 0; i < (solution->amountVertices - 1); i++){
            latency += verticesDistanceCalculator(solution->vertices[i], solution->vertices[i+1]);
        }

        solution->totalLatency += latency;

        removeFromListVertice(candidatesList, selectedVertice);

        paretoFrontIA[currentPFIASolution] = copySolutionWithoutPointer(solution, 1);

        currentPFIASolution++;

        free(restrictedCandidatesList);
    }

    free(candidatesList);
    free(solution->vertices);
    free(solution);

    return paretoFrontIA;
}




void twoExchange(Solution *solution, int verticePositionA, int verticePositionB, Vertice verticeA, Vertice verticeB){
    if (verticePositionA != solution->depotPosition && verticePositionB != solution->depotPosition){
        int previousPositionA = verticePositionA - 1;

        if (previousPositionA == -1){
            previousPositionA = (solution->amountVertices - 1);
        }

        int nextPositionA = verticePositionA + 1;

        Vertice temporaryVertice = verticeB;

        solution->travelCost -= verticesDistanceCalculator(solution->vertices[previousPositionA], solution->vertices[verticePositionA]);
        solution->travelCost -= verticesDistanceCalculator(solution->vertices[verticePositionA], solution->vertices[nextPositionA]);

        sumOrSubtractVerticeLatency(solution, verticePositionA, previousPositionA, 1);

        if (nextPositionA != verticePositionB && nextPositionA != solution->depotPosition){
            sumOrSubtractVerticeLatency(solution, verticePositionA, nextPositionA, 2);
        }

        int previousPositionB = verticePositionB - 1;
        int nextPositionB = verticePositionB + 1;

        if (nextPositionB == solution->amountVertices){
            nextPositionB = 0;
        }

        if (previousPositionB != verticePositionA){
            solution->travelCost -= verticesDistanceCalculator(solution->vertices[previousPositionB], solution->vertices[verticePositionB]);
        }

        solution->travelCost -= verticesDistanceCalculator(solution->vertices[verticePositionB], solution->vertices[nextPositionB]);

        sumOrSubtractVerticeLatency(solution, verticePositionB, previousPositionB, 1);

        if (nextPositionB != solution->depotPosition){
            sumOrSubtractVerticeLatency(solution, verticePositionB, nextPositionB, 2);
        }

        solution->vertices[verticePositionB] = verticeA;
        solution->vertices[verticePositionA] = temporaryVertice;

        solution->travelCost += verticesDistanceCalculator(solution->vertices[previousPositionA], solution->vertices[verticePositionA]);
        solution->travelCost += verticesDistanceCalculator(solution->vertices[verticePositionA], solution->vertices[nextPositionA]);

        sumOrSubtractVerticeLatency(solution, verticePositionA, previousPositionA, 3);
        sumOrSubtractVerticeLatency(solution, verticePositionB, previousPositionB, 3);

        if (nextPositionA != verticePositionB && nextPositionA != solution->depotPosition){
            sumOrSubtractVerticeLatency(solution, verticePositionA, nextPositionA, 4);
        }

        if (nextPositionB != solution->depotPosition){
            sumOrSubtractVerticeLatency(solution, verticePositionB, nextPositionB, 4);
        }

        if (previousPositionB != verticePositionA){
            solution->travelCost += verticesDistanceCalculator(solution->vertices[previousPositionB], solution->vertices[verticePositionB]);
        }

        solution->travelCost += verticesDistanceCalculator(solution->vertices[verticePositionB], solution->vertices[nextPositionB]);
    } else {
        solution->totalLatency = 0;
        int previousPositionA = verticePositionA - 1;

        if (previousPositionA == -1){
            previousPositionA = (solution->amountVertices - 1);
        }

        int nextPositionA = verticePositionA + 1;

        Vertice temporaryVertice = verticeB;

        solution->travelCost -= verticesDistanceCalculator(solution->vertices[previousPositionA], solution->vertices[verticePositionA]);
        solution->travelCost -= verticesDistanceCalculator(solution->vertices[verticePositionA], solution->vertices[nextPositionA]);

        int previousPositionB = verticePositionB - 1;
        int nextPositionB = verticePositionB + 1;

        if (nextPositionB == solution->amountVertices){
            nextPositionB = 0;
        }

        if (previousPositionB != verticePositionA){
            solution->travelCost -= verticesDistanceCalculator(solution->vertices[previousPositionB], solution->vertices[verticePositionB]);
        }

        solution->travelCost -= verticesDistanceCalculator(solution->vertices[verticePositionB], solution->vertices[nextPositionB]);

        solution->vertices[verticePositionB] = verticeA;
        solution->vertices[verticePositionA] = temporaryVertice;

        if (solution->vertices[verticePositionA].identification == 1){
            solution->depotPosition = verticePositionA;
        }

        if (solution->vertices[verticePositionB].identification == 1){
            solution->depotPosition = verticePositionB;
        }

        solution->travelCost += verticesDistanceCalculator(solution->vertices[previousPositionA], solution->vertices[verticePositionA]);
        solution->travelCost += verticesDistanceCalculator(solution->vertices[verticePositionA], solution->vertices[nextPositionA]);

        if (previousPositionB != verticePositionA){
            solution->travelCost += verticesDistanceCalculator(solution->vertices[previousPositionB], solution->vertices[verticePositionB]);
        }

        solution->travelCost += verticesDistanceCalculator(solution->vertices[verticePositionB], solution->vertices[nextPositionB]);

        for (int i = 0; i < solution->amountVertices; i++){
            if (i != solution->depotPosition){
                if ((i - 1) == -1){
                    sumOrSubtractVerticeLatency(solution, i, solution->amountVertices - 1, 3);
                }else{
                    sumOrSubtractVerticeLatency(solution, i, i - 1, 3);
                }
            }
        }
    }
}




Solution* transposonJumpAndSwap(Solution *solution){
    Solution *bestNeighbor = copySolution(solution);

    ListSolution *allNonDominatedNeighbors = createListSolution();

    onlyAddNonDominatedSolutions(allNonDominatedNeighbors, solution);

    int firstEdgePosition = rand() % solution->amountVertices;
    int randomAmount = rand() % solution->amountVertices + 1;

    while (randomAmount == solution->amountVertices){
        randomAmount = rand() % solution->amountVertices + 1;
    }

    int swapPositionA = firstEdgePosition;
    int swapPositionB = firstEdgePosition + 1;

    if (swapPositionB == solution->amountVertices){
        swapPositionB = 0;
    }

    for (int i = 0; i < randomAmount; i++){
        Solution *neighbor = copySolution(solution);

        twoExchange(neighbor, swapPositionA, swapPositionB, neighbor->vertices[swapPositionA], neighbor->vertices[swapPositionB]);

        onlyAddNonDominatedSolutions(allNonDominatedNeighbors, neighbor);

        swapPositionA++;

        if (swapPositionA == solution->amountVertices){
            swapPositionA = 0;
        }

        swapPositionB++;

        if (swapPositionB == solution->amountVertices){
            swapPositionB = 0;
        }

        if (randomAmount == (solution->amountVertices - 1) && i == (randomAmount - 1)){
            Solution *neighbor = copySolution(solution);

            twoExchange(neighbor, swapPositionA, swapPositionB, neighbor->vertices[swapPositionA], neighbor->vertices[swapPositionB]);

            onlyAddNonDominatedSolutions(allNonDominatedNeighbors, neighbor);

            swapPositionA++;

            if (swapPositionA == solution->amountVertices){
                swapPositionA = 0;
            }

            swapPositionB++;

            if (swapPositionB == solution->amountVertices){
                swapPositionB = 0;
            }

            free(neighbor->vertices);
            free(neighbor);
        }

        free(neighbor->vertices);
        free(neighbor);
    }

    int randomSolutionChosen = rand() % allNonDominatedNeighbors->size;

    int count = 0;

    for (NodeSolution *current = allNonDominatedNeighbors->head; current != NULL; current = current->next) {
        if (count == randomSolutionChosen){
            bestNeighbor->travelCost = current->solution->travelCost;
            bestNeighbor->totalLatency = current->solution->totalLatency;
            bestNeighbor->depotPosition = current->solution->depotPosition;

            for (int i = 0; i < solution->amountVertices; i++){
                bestNeighbor->vertices[i] = current->solution->vertices[i];
            }

            break;
        }

        count++;
    }

    return bestNeighbor;
}




Solution* transposonN1(Solution *solution){
    Solution *bestNeighbor = copySolution(solution);

    ListSolution *allNonDominatedNeighbors = createListSolution();

    onlyAddNonDominatedSolutions(allNonDominatedNeighbors, solution);

    int firstEdgePosition = rand() % solution->amountVertices;

    int randomAmount = rand() % solution->amountVertices + 1;

    while (randomAmount == solution->amountVertices){
        randomAmount = rand() % solution->amountVertices + 1;
    }

    int lastPosition = firstEdgePosition + randomAmount;

    if (lastPosition >= solution->amountVertices){
        lastPosition -= solution->amountVertices;
    }

    int afterLastPosition = lastPosition + 1;

    if (afterLastPosition == solution->amountVertices){
        afterLastPosition = 0;
    }

    for (int verticePositionA = firstEdgePosition; verticePositionA != lastPosition; verticePositionA++){
        for (int verticePositionB = (verticePositionA + 1); verticePositionB != afterLastPosition; verticePositionB++){
            if (verticePositionB == solution->amountVertices){
                verticePositionB = 0;
            }

            Solution *neighbor = copySolution(solution);

            twoExchange(neighbor, verticePositionA, verticePositionB, neighbor->vertices[verticePositionA], neighbor->vertices[verticePositionB]);

            onlyAddNonDominatedSolutions(allNonDominatedNeighbors, neighbor);

            if ((verticePositionB + 1) == solution->amountVertices){
                verticePositionB = -1;
            }

            free(neighbor->vertices);
            free(neighbor);
        }

        if ((verticePositionA + 1) == solution->amountVertices){
            verticePositionA = -1;
        }
    }

    int randomSolutionChosen = rand() % allNonDominatedNeighbors->size;

    int count = 0;

    for (NodeSolution *current = allNonDominatedNeighbors->head; current != NULL; current = current->next) {
        if (count == randomSolutionChosen){
            bestNeighbor->travelCost = current->solution->travelCost;
            bestNeighbor->totalLatency = current->solution->totalLatency;
            bestNeighbor->depotPosition = current->solution->depotPosition;

            for (int i = 0; i < solution->amountVertices; i++){
                bestNeighbor->vertices[i] = current->solution->vertices[i];
            }

            break;
        }

        count++;
    }

    return bestNeighbor;
}




Solution* transposonN2(Solution *solution, Vertice *allVertices, int numVertices){
    int *containedVertices = calloc(numVertices + 1, sizeof(int));

    for (int i = 0; i < solution->amountVertices; i++){
        containedVertices[solution->vertices[i].identification] = 1;
    }

    int *notContainedVertices = malloc(((numVertices - 1) - (solution->amountVertices - 1)) * sizeof(int));

    int currentPosition = 0;

    for (int i = 2; i < (numVertices + 1); i++){
        if (containedVertices[i] == 0){
            notContainedVertices[currentPosition] = i;

            currentPosition++;

            if (currentPosition == ((numVertices - 1) - (solution->amountVertices - 1))){
                break;
            }
        }
    }

    Solution *bestNeighbor = copySolution(solution);

    ListSolution *allNonDominatedNeighbors = createListSolution();

    onlyAddNonDominatedSolutions(allNonDominatedNeighbors, solution);

    int firstEdgePosition = rand() % solution->amountVertices;
    int randomAmount = rand() % solution->amountVertices + 1;

    while (randomAmount == solution->amountVertices){
        randomAmount = rand() % solution->amountVertices + 1;
    }

    int oldVerticePosition = firstEdgePosition;

    for (int i = 0; i < (randomAmount + 1); i++){
        if (oldVerticePosition != solution->depotPosition){
            int previousPosition = oldVerticePosition - 1;
            int nextPosition = oldVerticePosition + 1;

            if (previousPosition == -1){
                previousPosition = (solution->amountVertices - 1);
            }

            if (nextPosition == solution->amountVertices){
                nextPosition = 0;
            }

            for (int NewVertice = 0; NewVertice < ((numVertices - 1) - (solution->amountVertices - 1)); NewVertice++){
                int newVerticePosition = notContainedVertices[NewVertice] - 1;

                Solution *neighbor = copySolution(solution);

                neighbor->travelCost -= verticesDistanceCalculator(neighbor->vertices[previousPosition], neighbor->vertices[oldVerticePosition]);
                neighbor->travelCost -= verticesDistanceCalculator(neighbor->vertices[oldVerticePosition], neighbor->vertices[nextPosition]);
                neighbor->totalProfit -= neighbor->vertices[oldVerticePosition].profit;

                sumOrSubtractVerticeLatency(neighbor, oldVerticePosition, previousPosition, 1);

                if (nextPosition != solution->depotPosition){
                    sumOrSubtractVerticeLatency(neighbor, oldVerticePosition, nextPosition, 2);
                }

                neighbor->vertices[oldVerticePosition] = allVertices[newVerticePosition];

                neighbor->travelCost += verticesDistanceCalculator(neighbor->vertices[previousPosition], neighbor->vertices[oldVerticePosition]);
                neighbor->travelCost += verticesDistanceCalculator(neighbor->vertices[oldVerticePosition], neighbor->vertices[nextPosition]);
                neighbor->totalProfit += neighbor->vertices[oldVerticePosition].profit;

                sumOrSubtractVerticeLatency(neighbor, oldVerticePosition, previousPosition, 3);

                if (nextPosition != solution->depotPosition){
                    sumOrSubtractVerticeLatency(neighbor, oldVerticePosition, nextPosition, 4);
                }

                onlyAddNonDominatedSolutions(allNonDominatedNeighbors, neighbor);

                free(neighbor->vertices);
                free(neighbor);
            }
        }

        if ((oldVerticePosition + 1) == solution->amountVertices){
            oldVerticePosition = -1;
        }

        oldVerticePosition++;
    }

    int randomSolutionChosen = rand() % allNonDominatedNeighbors->size;

    int count = 0;

    for (NodeSolution *current = allNonDominatedNeighbors->head; current != NULL; current = current->next) {
        if (count == randomSolutionChosen){
            bestNeighbor->travelCost = current->solution->travelCost;
            bestNeighbor->totalLatency = current->solution->totalLatency;
            bestNeighbor->depotPosition = current->solution->depotPosition;

            for (int i = 0; i < solution->amountVertices; i++){
                bestNeighbor->vertices[i] = current->solution->vertices[i];
            }

            break;
        }

        count++;
    }

    free(containedVertices);
    free(notContainedVertices);
    return bestNeighbor;
}




VerticeTree* minimunSpanningTreePrim(Vertice *allVertices, int numVertices){
    VerticeTree *originalTree = malloc(numVertices * sizeof(VerticeTree));

    int randomRoot = rand() % numVertices;

    originalTree[randomRoot].identification = allVertices[randomRoot].identification;
    originalTree[randomRoot].coordinateX = allVertices[randomRoot].coordinateX;
    originalTree[randomRoot].coordinateY = allVertices[randomRoot].coordinateY;
    originalTree[randomRoot].profit = allVertices[randomRoot].profit;
    originalTree[randomRoot].key = 0;
    originalTree[randomRoot].parentVertice = 0;

    ListVerticeTree *priorityList = createListVerticeTree();

    NodeVerticeTree *lastNode = NULL;

    for (int i = 0; i < numVertices; i++) {
        if (allVertices[i].identification != originalTree[randomRoot].identification){
            VerticeTree *temporaryVertice = malloc(sizeof(VerticeTree));

            temporaryVertice->identification = allVertices[i].identification;
            temporaryVertice->coordinateX = allVertices[i].coordinateX;
            temporaryVertice->coordinateY = allVertices[i].coordinateY;
            temporaryVertice->profit = allVertices[i].profit;
            temporaryVertice->key = verticesDistanceCalculator(allVertices[randomRoot], allVertices[i]);
            temporaryVertice->parentVertice = originalTree[randomRoot].identification;

            lastNode = addToListListVerticeTree(priorityList, temporaryVertice, lastNode);
        }
    }

    VerticeTree *bestTemporaryVertice = malloc(sizeof(VerticeTree));
    bestTemporaryVertice->parentVertice = 0;

    while (!isListVerticeTreeEmpty(priorityList)){
        int firstListChecker = 0;

        for (NodeVerticeTree *current = priorityList->head; current != NULL; current = current->next){
            if (firstListChecker == 0){
                bestTemporaryVertice->identification = current->verticeTree->identification;
                bestTemporaryVertice->coordinateX = current->verticeTree->coordinateX;
                bestTemporaryVertice->coordinateY = current->verticeTree->coordinateY;
                bestTemporaryVertice->profit = current->verticeTree->profit;
                bestTemporaryVertice->key = current->verticeTree->key;
                bestTemporaryVertice->parentVertice = current->verticeTree->parentVertice;

                firstListChecker = 1;
            } else{
                if (current->verticeTree->key < bestTemporaryVertice->key){
                    bestTemporaryVertice->identification = current->verticeTree->identification;
                    bestTemporaryVertice->coordinateX = current->verticeTree->coordinateX;
                    bestTemporaryVertice->coordinateY = current->verticeTree->coordinateY;
                    bestTemporaryVertice->profit = current->verticeTree->profit;
                    bestTemporaryVertice->key = current->verticeTree->key;
                    bestTemporaryVertice->parentVertice = current->verticeTree->parentVertice;
                }
            }
        }

        removeFromListVerticeTree(priorityList, bestTemporaryVertice);

        int position = bestTemporaryVertice->identification - 1;

        originalTree[position].identification = bestTemporaryVertice->identification;
        originalTree[position].coordinateX = bestTemporaryVertice->coordinateX;
        originalTree[position].coordinateY = bestTemporaryVertice->coordinateY;
        originalTree[position].profit = bestTemporaryVertice->profit;
        originalTree[position].key = bestTemporaryVertice->key;
        originalTree[position].parentVertice = bestTemporaryVertice->parentVertice;

        for (NodeVerticeTree *current = priorityList->head; current != NULL; current = current->next){
            double newKey = verticesDistanceCalculator(allVertices[current->verticeTree->identification - 1], allVertices[originalTree[position].identification - 1]);

            if (newKey < current->verticeTree->key){
                current->verticeTree->key = newKey;
                current->verticeTree->parentVertice = originalTree[position].identification;
            }
        }
    }

    free(bestTemporaryVertice);

    return originalTree;
}




Solution* plasmidPriori(VerticeTree *minimunSpanningTree, Vertice *allVertices, int numVertices){
    int randomGeneticInfoStart = rand() % numVertices;

    while (minimunSpanningTree[randomGeneticInfoStart].parentVertice == 0){
        randomGeneticInfoStart = rand() % numVertices;
    }

    int depotVerification = 0;
    int secondaryVertice = 0;
    int amountVerticesInPath = 0;
    int predeterminedAmount = 0.25 * numVertices;
    int randomPercentage = rand() % predeterminedAmount + 1;

    int *containedVertices = calloc(randomPercentage, sizeof(int));

    containedVertices[0] = minimunSpanningTree[randomGeneticInfoStart].identification;

    if (containedVertices[0] == 1){
        depotVerification = 1;
    }

    containedVertices[1] = minimunSpanningTree[randomGeneticInfoStart].parentVertice;

    if (containedVertices[1] == 1){
        depotVerification = 1;
    }

    amountVerticesInPath = 2;

    secondaryVertice = minimunSpanningTree[containedVertices[1] - 1].parentVertice;

    for (int i = 2; i < randomPercentage; i++){
        if (secondaryVertice != 0){
            containedVertices[i] = secondaryVertice;

            if (containedVertices[i] == 1){
                depotVerification = 1;
            }

            amountVerticesInPath++;
            secondaryVertice = minimunSpanningTree[containedVertices[i] - 1].parentVertice;
        } else{
            break;
        }
    }

    Solution *plasmidSolution = malloc(sizeof(Solution));

    plasmidSolution->amountVertices = 0;
    plasmidSolution->depotPosition = -1;
    plasmidSolution->totalLatency = 0;
    plasmidSolution->totalProfit = 0;
    plasmidSolution->travelCost = 0;

    if (depotVerification == 1){
        plasmidSolution->vertices = malloc((amountVerticesInPath - 1) * sizeof(Vertice));
    } else{
        plasmidSolution->vertices = malloc(amountVerticesInPath * sizeof(Vertice));
    }

    int order = rand() % 2;

    if (order == 0){
        int supportCounter = 0;

        for (int i = 0; i < amountVerticesInPath; i++){
            if (allVertices[containedVertices[i] - 1].identification != 1){
                plasmidSolution->vertices[supportCounter].identification = allVertices[containedVertices[i] - 1].identification;
                plasmidSolution->vertices[supportCounter].coordinateX = allVertices[containedVertices[i] - 1].coordinateX;
                plasmidSolution->vertices[supportCounter].coordinateY = allVertices[containedVertices[i] - 1].coordinateY;
                plasmidSolution->vertices[supportCounter].profit = allVertices[containedVertices[i] - 1].profit;

                plasmidSolution->totalProfit += allVertices[containedVertices[i] - 1].profit;

                plasmidSolution->amountVertices++;

                double latency = 0;

                for (int i = 0; i < (plasmidSolution->amountVertices - 1); i++){
                    latency += verticesDistanceCalculator(plasmidSolution->vertices[i], plasmidSolution->vertices[i+1]);
                }

                plasmidSolution->totalLatency += latency;

                if (supportCounter > 0){
                    plasmidSolution->travelCost += verticesDistanceCalculator(plasmidSolution->vertices[supportCounter - 1], plasmidSolution->vertices[supportCounter]);
                }

                supportCounter++;
            }
        }
    } else{
        int supportCounter = 0;

        for (int i = amountVerticesInPath - 1; i > -1; i--){
            if (allVertices[containedVertices[i] - 1].identification != 1){
                plasmidSolution->vertices[supportCounter].identification = allVertices[containedVertices[i] - 1].identification;
                plasmidSolution->vertices[supportCounter].coordinateX = allVertices[containedVertices[i] - 1].coordinateX;
                plasmidSolution->vertices[supportCounter].coordinateY = allVertices[containedVertices[i] - 1].coordinateY;
                plasmidSolution->vertices[supportCounter].profit = allVertices[containedVertices[i] - 1].profit;

                plasmidSolution->totalProfit += allVertices[containedVertices[i] - 1].profit;

                plasmidSolution->amountVertices++;

                double latency = 0;

                for (int i = 0; i < (plasmidSolution->amountVertices - 1); i++){
                    latency += verticesDistanceCalculator(plasmidSolution->vertices[i], plasmidSolution->vertices[i+1]);
                }

                plasmidSolution->totalLatency += latency;

                if (supportCounter > 0){
                    plasmidSolution->travelCost += verticesDistanceCalculator(plasmidSolution->vertices[supportCounter - 1], plasmidSolution->vertices[supportCounter]);
                }

                supportCounter++;
            }
        }
    }

    free(containedVertices);

    return plasmidSolution;
}




Solution* plasmidPrioriCreator(VerticeTree *minimunSpanningTree, Vertice *allVertices, int numVertices){
    Solution *candidatePlasmids = malloc(30 * sizeof(Solution));

    for (int i = 0; i < 30; i++){
        Solution *temporaryPlasmid = plasmidPriori(minimunSpanningTree, allVertices, numVertices);

        candidatePlasmids[i] = copySolutionWithoutPointer(temporaryPlasmid, 0);

        free(temporaryPlasmid->vertices);
        free(temporaryPlasmid);
    }

    ListSolution *nonDominatedPlasmids = createListSolution();

    for (int i = 0; i < 30; i++){
        onlyAddNonDominatedSolutions(nonDominatedPlasmids, &candidatePlasmids[i]);
    }

    Solution *chosenPlasmid = malloc(sizeof(Solution));

    int randomPlasmidPosition = rand() % nonDominatedPlasmids->size;
    int supportCounter = 0;

    for (NodeSolution *node = nonDominatedPlasmids->head; node != NULL; node = node->next){
        if (supportCounter == randomPlasmidPosition){
            chosenPlasmid->amountVertices = node->solution->amountVertices;
            chosenPlasmid->depotPosition = node->solution->depotPosition;
            chosenPlasmid->totalLatency = node->solution->totalLatency;
            chosenPlasmid->totalProfit = node->solution->totalProfit;
            chosenPlasmid->travelCost = node->solution->travelCost;

            chosenPlasmid->vertices = malloc(node->solution->amountVertices * sizeof(Vertice));

            for (int i = 0; i < node->solution->amountVertices; i++){
                chosenPlasmid->vertices[i] = node->solution->vertices[i];
            }

            break;
        }

        supportCounter++;
    }

    for (int i = 0; i < 30; i++){
        free(candidatePlasmids[i].vertices);
    }

    free(candidatePlasmids);

    return chosenPlasmid;
}




void updatePosterioriSolutions(PosterioriInformation *posterioriSolutionsInformation, Solution *newSolution){
    if (posterioriSolutionsInformation->amountSolutions == 0){
        posterioriSolutionsInformation->solutions[0].amountVertices = newSolution->amountVertices;
        posterioriSolutionsInformation->solutions[0].depotPosition = newSolution->depotPosition;
        posterioriSolutionsInformation->solutions[0].totalLatency = newSolution->totalLatency;
        posterioriSolutionsInformation->solutions[0].totalProfit = newSolution->totalProfit;
        posterioriSolutionsInformation->solutions[0].travelCost = newSolution->travelCost;

        posterioriSolutionsInformation->solutions[0].vertices = malloc(newSolution->amountVertices * sizeof(Vertice));

        for (int i = 0; i < newSolution->amountVertices; i++){
            posterioriSolutionsInformation->solutions[0].vertices[i] = newSolution->vertices[i];
        }

        posterioriSolutionsInformation->amountSolutions = 1;
    } else if (posterioriSolutionsInformation->amountSolutions < 4){
        int acceptance = 1;

        for (int i = 0; i < 4; i++){
            if (posterioriSolutionsInformation->solutions[i].depotPosition != -1){
                if (dominance(&posterioriSolutionsInformation->solutions[i], newSolution)){
                    acceptance = 0;
                    break;
                }
            }
        }

        if (acceptance == 1){
            int insertionPosition = 0;

            for (int i = 0; i < 4; i++){
                if (posterioriSolutionsInformation->solutions[i].depotPosition == -1){
                    insertionPosition = i;
                }

                if (posterioriSolutionsInformation->solutions[i].depotPosition != -1){
                    if (dominance(newSolution, &posterioriSolutionsInformation->solutions[i])){
                        posterioriSolutionsInformation->solutions[i].depotPosition = -1;

                        posterioriSolutionsInformation->amountSolutions--;
                    }
                }
            }

            posterioriSolutionsInformation->solutions[insertionPosition].amountVertices = newSolution->amountVertices;
            posterioriSolutionsInformation->solutions[insertionPosition].depotPosition = newSolution->depotPosition;
            posterioriSolutionsInformation->solutions[insertionPosition].totalLatency = newSolution->totalLatency;
            posterioriSolutionsInformation->solutions[insertionPosition].totalProfit = newSolution->totalProfit;
            posterioriSolutionsInformation->solutions[insertionPosition].travelCost = newSolution->travelCost;

            posterioriSolutionsInformation->solutions[insertionPosition].vertices = malloc(newSolution->amountVertices * sizeof(Vertice));

            for (int i = 0; i < newSolution->amountVertices; i++){
                posterioriSolutionsInformation->solutions[insertionPosition].vertices[i] = newSolution->vertices[i];
            }

            posterioriSolutionsInformation->amountSolutions++;
        }
    } else{
        int acceptance = 1;

        for (int i = 0; i < 4; i++){
            if (dominance(&posterioriSolutionsInformation->solutions[i], newSolution)){
                acceptance = 0;

                break;
            }
        }

        if (acceptance == 1){
            int removalVerification = 0;
            int insertionPosition = 0;

            for (int i = 0; i < 4; i++){
                if (dominance(newSolution, &posterioriSolutionsInformation->solutions[i])){
                    removalVerification = 1;
                    insertionPosition = i;

                    posterioriSolutionsInformation->solutions[i].depotPosition = -1;

                    posterioriSolutionsInformation->amountSolutions--;
                }
            }

            if (removalVerification == 1){
                posterioriSolutionsInformation->solutions[insertionPosition].amountVertices = newSolution->amountVertices;
                posterioriSolutionsInformation->solutions[insertionPosition].depotPosition = newSolution->depotPosition;
                posterioriSolutionsInformation->solutions[insertionPosition].totalLatency = newSolution->totalLatency;
                posterioriSolutionsInformation->solutions[insertionPosition].totalProfit = newSolution->totalProfit;
                posterioriSolutionsInformation->solutions[insertionPosition].travelCost = newSolution->travelCost;

                posterioriSolutionsInformation->solutions[insertionPosition].vertices = malloc(newSolution->amountVertices * sizeof(Vertice));

                for (int i = 0; i < newSolution->amountVertices; i++){
                    posterioriSolutionsInformation->solutions[insertionPosition].vertices[i] = newSolution->vertices[i];
                }

                posterioriSolutionsInformation->amountSolutions++;
            } else{
                int randomPosition = rand() % 4;

                posterioriSolutionsInformation->solutions[randomPosition].amountVertices = newSolution->amountVertices;
                posterioriSolutionsInformation->solutions[randomPosition].depotPosition = newSolution->depotPosition;
                posterioriSolutionsInformation->solutions[randomPosition].totalLatency = newSolution->totalLatency;
                posterioriSolutionsInformation->solutions[randomPosition].totalProfit = newSolution->totalProfit;
                posterioriSolutionsInformation->solutions[randomPosition].travelCost = newSolution->travelCost;

                posterioriSolutionsInformation->solutions[randomPosition].vertices = malloc(newSolution->amountVertices * sizeof(Vertice));

                for (int i = 0; i < newSolution->amountVertices; i++){
                    posterioriSolutionsInformation->solutions[randomPosition].vertices[i] = newSolution->vertices[i];
                }
            }
        }
    }
}




Solution* plasmidPosteriori(PosterioriInformation *posterioriSolutionsInformation, int posterioriSolutionPosition, Vertice *allVertices, int numVertices){
    int *containedVertices = calloc((posterioriSolutionsInformation->solutions[posterioriSolutionPosition].amountVertices - 1), sizeof(int));

    int counter = 0;

    for (int i = 0; i < posterioriSolutionsInformation->solutions[posterioriSolutionPosition].amountVertices; i++){
        if (posterioriSolutionsInformation->solutions[posterioriSolutionPosition].vertices[i].identification != 1){
            containedVertices[counter] = posterioriSolutionsInformation->solutions[posterioriSolutionPosition].vertices[i].identification;
            counter++;
        }
    }

    Solution *plasmidSolution = malloc(sizeof(Solution));

    plasmidSolution->amountVertices = 0;
    plasmidSolution->depotPosition = -1;
    plasmidSolution->totalLatency = 0;
    plasmidSolution->totalProfit = 0;
    plasmidSolution->travelCost = 0;
    plasmidSolution->vertices = malloc((posterioriSolutionsInformation->solutions[posterioriSolutionPosition].amountVertices - 1) * sizeof(Vertice));

    int order = rand() % 2;

    if (order == 0){
        for (int i = 0; i < (posterioriSolutionsInformation->solutions[posterioriSolutionPosition].amountVertices - 1); i++){
            plasmidSolution->vertices[i].identification = allVertices[containedVertices[i] - 1].identification;
            plasmidSolution->vertices[i].coordinateX = allVertices[containedVertices[i] - 1].coordinateX;
            plasmidSolution->vertices[i].coordinateY = allVertices[containedVertices[i] - 1].coordinateY;
            plasmidSolution->vertices[i].profit = allVertices[containedVertices[i] - 1].profit;

            plasmidSolution->totalProfit += allVertices[containedVertices[i] - 1].profit;

            plasmidSolution->amountVertices++;

            double latency = 0;

            for (int i = 0; i < (plasmidSolution->amountVertices - 1); i++){
                latency += verticesDistanceCalculator(plasmidSolution->vertices[i], plasmidSolution->vertices[i+1]);
            }

            plasmidSolution->totalLatency += latency;

            if (i > 0){
                plasmidSolution->travelCost += verticesDistanceCalculator(plasmidSolution->vertices[i - 1], plasmidSolution->vertices[i]);
            }
        }
    } else{
        int supportCounter = 0;

        for (int i = (posterioriSolutionsInformation->solutions[posterioriSolutionPosition].amountVertices - 1) - 1; i > -1; i--){
            plasmidSolution->vertices[supportCounter].identification = allVertices[containedVertices[i] - 1].identification;
            plasmidSolution->vertices[supportCounter].coordinateX = allVertices[containedVertices[i] - 1].coordinateX;
            plasmidSolution->vertices[supportCounter].coordinateY = allVertices[containedVertices[i] - 1].coordinateY;
            plasmidSolution->vertices[supportCounter].profit = allVertices[containedVertices[i] - 1].profit;

            plasmidSolution->totalProfit += allVertices[containedVertices[i] - 1].profit;

            plasmidSolution->amountVertices++;

            double latency = 0;

            for (int i = 0; i < (plasmidSolution->amountVertices - 1); i++){
                latency += verticesDistanceCalculator(plasmidSolution->vertices[i], plasmidSolution->vertices[i+1]);
            }

            plasmidSolution->totalLatency += latency;

            if (supportCounter > 0){
                plasmidSolution->travelCost += verticesDistanceCalculator(plasmidSolution->vertices[supportCounter - 1], plasmidSolution->vertices[supportCounter]);
            }

            supportCounter++;
        }
    }

    free(containedVertices);
    return plasmidSolution;
}




Solution* plasmidPosterioriCreator(PosterioriInformation *posterioriSolutionsInformation, Vertice *allVertices, int numVertices){
    int candidatePlasmidsAmount = posterioriSolutionsInformation->amountSolutions;

    Solution *candidatePlasmids = malloc(candidatePlasmidsAmount * sizeof(Solution));

    int counter = 0;

    for (int i = 0; i < 4; i++){
        if (posterioriSolutionsInformation->solutions[i].depotPosition != -1){
            Solution *temporaryPlasmid = plasmidPosteriori(posterioriSolutionsInformation, i, allVertices, numVertices);

            candidatePlasmids[counter] = copySolutionWithoutPointer(temporaryPlasmid, 0);

            counter++;

            free(temporaryPlasmid->vertices);
            free(temporaryPlasmid);
        }
    }

    Solution *chosenPlasmid = malloc(sizeof(Solution));

    int randomPlasmidPosition = rand() % candidatePlasmidsAmount;

    chosenPlasmid->amountVertices = candidatePlasmids[randomPlasmidPosition].amountVertices;
    chosenPlasmid->depotPosition = candidatePlasmids[randomPlasmidPosition].depotPosition;
    chosenPlasmid->totalLatency = candidatePlasmids[randomPlasmidPosition].totalLatency;
    chosenPlasmid->totalProfit = candidatePlasmids[randomPlasmidPosition].totalProfit;
    chosenPlasmid->travelCost = candidatePlasmids[randomPlasmidPosition].travelCost;

    chosenPlasmid->vertices = malloc(candidatePlasmids[randomPlasmidPosition].amountVertices * sizeof(Vertice));

    for (int i = 0; i < candidatePlasmids[randomPlasmidPosition].amountVertices; i++){
        chosenPlasmid->vertices[i] = candidatePlasmids[randomPlasmidPosition].vertices[i];
    }

    for (int i = 0; i < counter; i++){
        free(candidatePlasmids[i].vertices);
    }

    free(candidatePlasmids);
    return chosenPlasmid;
}




Solution* plasmidSolutionAlteration(Solution *solution, Solution *plasmid, int numVertices){
    int insertionPoint = rand() % solution->amountVertices;

    while (insertionPoint == solution->depotPosition){
        insertionPoint = rand() % solution->amountVertices;
    }

    int *containedVertices = calloc(numVertices + 1, sizeof(int));

    for (int i = 0; i < solution->amountVertices; i++){
        containedVertices[solution->vertices[i].identification] = 1;
    }

    int supportMemorySize = solution->amountVertices;

    for (int i = 0; i < plasmid->amountVertices; i++){
        if (containedVertices[plasmid->vertices[i].identification] != 1){
            supportMemorySize++;
        }
    }

    Vertice *supportMemory = malloc(supportMemorySize * sizeof(Vertice));

    int temporaryPositionInSolution = 0;
    int temporaryPositionForPlasmid = 0;

    for (int i = 0; i < solution->amountVertices; i++){
        supportMemory[i] = solution->vertices[i];

        if (i == insertionPoint){
            temporaryPositionInSolution = i + 1;
            temporaryPositionForPlasmid = i + 1;

            break;
        }
    }

    for (int i = 0; i < plasmid->amountVertices; i++){
        if (containedVertices[plasmid->vertices[i].identification] != 1){
            supportMemory[temporaryPositionForPlasmid] = plasmid->vertices[i];
            temporaryPositionForPlasmid++;
        }
    }

    if (temporaryPositionForPlasmid != supportMemorySize){
        for (int i = temporaryPositionInSolution; i < solution->amountVertices; i++){
            supportMemory[temporaryPositionForPlasmid] = solution->vertices[i];
            temporaryPositionForPlasmid++;
        }
    }

    free(solution->vertices);

    solution->amountVertices = supportMemorySize;
    solution->travelCost = 0;
    solution->totalLatency = 0;
    solution->totalProfit = 0;

    solution->vertices = malloc(supportMemorySize * sizeof(Vertice));

    for (int i = 0; i < supportMemorySize; i++){
        solution->vertices[i] = supportMemory[i];
    }

    solutionTotalTravelCostAndProfit(solution);
    solutionTotalLatency(solution);

    free(containedVertices);
    free(supportMemory);
    return solution;
}




int betterSolution(ListSolution *allNonDominatedSolutions, Solution *originalSolution, Solution *alteredSolution){
    if (dominance(alteredSolution, originalSolution) == 1){
        return 1;
    } else{
        int listDominance = 1;

        for (NodeSolution *node = allNonDominatedSolutions->head; node != NULL; node = node->next){
            if (dominance(node->solution, alteredSolution) == 1){
                listDominance = 0;
            }
        }

        return listDominance;
    }
}




int chooseAplhaValue(){
    int alphaPicked;

    printf("Selecione um dos valores abaixo para alpha:\n\n");
    printf("1 - alpha = 0.00\n");
    printf("2 - alpha = 0.25\n");
    printf("3 - alpha = 0.50\n");
    printf("4 - alpha = 0.75\n");
    printf("5 - alpha = 1.00\n\n");
    printf("Digite sua opcao: ");
    scanf("%d", &alphaPicked);

    while (alphaPicked < 1 || alphaPicked > 5){
        printf("\nErro!\n\n");
        printf("Digite sua opcao: ");
        scanf("%d", &alphaPicked);
    }

    return alphaPicked;
}




int chooseGamaValue(){
    int gamaPicked;

    printf("\nSelecione um dos valores abaixo para gama:\n\n");
    printf("1 - gama = 0.25\n");
    printf("2 - gama = 0.50\n");
    printf("3 - gama = 0.75\n");
    printf("4 - gama = 1.00\n\n");
    printf("Digite sua opcao: ");
    scanf("%d", &gamaPicked);

    while (gamaPicked < 1 || gamaPicked > 4){
        printf("\nErro!\n\n");
        printf("Digite sua opcao: ");
        scanf("%d", &gamaPicked);
    }

    printf("\n");

    return gamaPicked;
}




double assignAlphaValue(int alphaPicked){
    double alpha;

    switch (alphaPicked){
        case 1:
            alpha = 0;
            break;
        case 2:
            alpha = 0.25;
            break;
        case 3:
            alpha = 0.50;
            break;
        case 4:
            alpha = 0.75;
            break;
        case 5:
            alpha = 1;
            break;
        default:
            break;
    }

    return alpha;
}




double assignGamaValue(int gamaPicked){
    double gama;

    switch (gamaPicked){
        case 1:
            gama = 0.25;
            break;
        case 2:
            gama = 0.50;
            break;
        case 3:
            gama = 0.75;
            break;
        case 4:
            gama = 1;
            break;
        default:
            break;
    }

    return gama;
}




void transgeneticMainLoop(Vertice *allVertices, int numVertices, double alpha, double gama){
    clock_t start, end, pauseStart, pauseEnd;
    double cpuTimeUsed;

    start = clock();

    Solution *paretoFrontIA = paretoFrontInitialAproximationConstructor(numVertices, allVertices, alpha);

    pauseStart = clock();

    FILE *outfile = fopen("1.1 ValoresCustoViajemSoluçõesIniciais.in", "w");
    if (outfile == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    FILE *outfile2 = fopen("1.2 ValoresLatênciaSoluçõesIniciais.in", "w");
    if (outfile2 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    FILE *outfile3 = fopen("1.3 ValoresLucroSoluçõesIniciais.in", "w");
    if (outfile2 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < (numVertices - 1); i++){
        fprintf(outfile, "%.2lf\n", paretoFrontIA[i].travelCost);
        fprintf(outfile2, "%.2lf\n", paretoFrontIA[i].totalLatency);
        fprintf(outfile3, "%d\n", paretoFrontIA[i].totalProfit);
    }

    fclose(outfile);
    fclose(outfile2);
    fclose(outfile3);

    pauseEnd = clock();

    ListSolution *allNonDominatedSolutions = createListSolution();

    for (int i = 0; i < (numVertices - 1); i++){
        onlyAddNonDominatedSolutions(allNonDominatedSolutions, &paretoFrontIA[i]);
    }

    VerticeTree *prioriPrimTree = minimunSpanningTreePrim(allVertices, numVertices);

    PosterioriInformation *posterioriSolutionsInformation = malloc(sizeof(PosterioriInformation));

    posterioriSolutionsInformation->solutions = malloc(4 * sizeof(Solution));
    posterioriSolutionsInformation->amountSolutions = 0;

    for (int i = 0; i < 4; i++){
        posterioriSolutionsInformation->solutions[i].depotPosition = -1;
    }

    int numGenerations = 30;
    int probPlasmid = 50;
    int probIncreaseFactor = 10;
    int iterationsForNewSet = 4;
    int iterationCounter = 0;

    for (int i = 0; i < numGenerations; i++){
        if (iterationCounter == iterationsForNewSet){
            probPlasmid += probIncreaseFactor;
            iterationCounter = 0;
        }

        for (int j = 0; j < (numVertices - 1); j++){
            int vectorChosen = rand() % 100 + 1;

            if (vectorChosen <= probPlasmid){
                Solution *plasmid = malloc(sizeof(Solution));

                if (posterioriSolutionsInformation->amountSolutions > 0){
                    int plasmidMaterialOrigins = rand() % 2;

                    if (plasmidMaterialOrigins == 0){
                        plasmid = plasmidPosterioriCreator(posterioriSolutionsInformation, allVertices, numVertices);
                    } else {
                        plasmid = plasmidPrioriCreator(prioriPrimTree, allVertices, numVertices);
                    }
                } else {
                    plasmid = plasmidPrioriCreator(prioriPrimTree, allVertices, numVertices);
                }

                Solution *alteredSolution = copySolution(&paretoFrontIA[j]);

                alteredSolution = plasmidSolutionAlteration(alteredSolution, plasmid, numVertices);

                if (betterSolution(allNonDominatedSolutions, &paretoFrontIA[j], alteredSolution) == 1){
                    paretoFrontIA[j].amountVertices = alteredSolution->amountVertices;
                    paretoFrontIA[j].depotPosition = alteredSolution->depotPosition;
                    paretoFrontIA[j].totalLatency = alteredSolution->totalLatency;
                    paretoFrontIA[j].totalProfit = alteredSolution->totalProfit;
                    paretoFrontIA[j].travelCost = alteredSolution->travelCost;

                    paretoFrontIA[j].vertices = malloc(alteredSolution->amountVertices * sizeof(Vertice));

                    for (int k = 0; k < alteredSolution->amountVertices; k++){
                        paretoFrontIA[j].vertices[k] = alteredSolution->vertices[k];
                    }
                }

                onlyAddNonDominatedSolutions(allNonDominatedSolutions, alteredSolution);

                updatePosterioriSolutions(posterioriSolutionsInformation, alteredSolution);

                free(alteredSolution->vertices);
                free(alteredSolution);
                free(plasmid->vertices);
                free(plasmid);
            } else {
                int transposonChosen = rand() % 3 + 1;

                Solution *alteredSolution = copySolution(&paretoFrontIA[j]);

                while ((transposonChosen == 3 && alteredSolution->amountVertices == numVertices) || (transposonChosen != 3 && alteredSolution->amountVertices < 3)){
                    transposonChosen = rand() % 3 + 1;
                }

                switch(transposonChosen){
                    case 1:
                        alteredSolution = transposonJumpAndSwap(alteredSolution);

                        if (betterSolution(allNonDominatedSolutions, &paretoFrontIA[j], alteredSolution) == 1){
                            paretoFrontIA[j].amountVertices = alteredSolution->amountVertices;
                            paretoFrontIA[j].depotPosition = alteredSolution->depotPosition;
                            paretoFrontIA[j].totalLatency = alteredSolution->totalLatency;
                            paretoFrontIA[j].totalProfit = alteredSolution->totalProfit;
                            paretoFrontIA[j].travelCost = alteredSolution->travelCost;

                            paretoFrontIA[j].vertices = malloc(alteredSolution->amountVertices * sizeof(Vertice));

                            for (int k = 0; k < alteredSolution->amountVertices; k++){
                                paretoFrontIA[j].vertices[k] = alteredSolution->vertices[k];
                            }
                        }

                        onlyAddNonDominatedSolutions(allNonDominatedSolutions, alteredSolution);

                        updatePosterioriSolutions(posterioriSolutionsInformation, alteredSolution);

                        free(alteredSolution->vertices);
                        free(alteredSolution);
                        break;
                    case 2:
                        alteredSolution = transposonN1(alteredSolution);

                        if (betterSolution(allNonDominatedSolutions, &paretoFrontIA[j], alteredSolution) == 1){
                            paretoFrontIA[j].amountVertices = alteredSolution->amountVertices;
                            paretoFrontIA[j].depotPosition = alteredSolution->depotPosition;
                            paretoFrontIA[j].totalLatency = alteredSolution->totalLatency;
                            paretoFrontIA[j].totalProfit = alteredSolution->totalProfit;
                            paretoFrontIA[j].travelCost = alteredSolution->travelCost;

                            paretoFrontIA[j].vertices = malloc(alteredSolution->amountVertices * sizeof(Vertice));

                            for (int k = 0; k < alteredSolution->amountVertices; k++){
                                paretoFrontIA[j].vertices[k] = alteredSolution->vertices[k];
                            }
                        }

                        onlyAddNonDominatedSolutions(allNonDominatedSolutions, alteredSolution);

                        updatePosterioriSolutions(posterioriSolutionsInformation, alteredSolution);

                        free(alteredSolution->vertices);
                        free(alteredSolution);
                        break;
                    case 3:
                        alteredSolution = transposonN2(alteredSolution, allVertices, numVertices);

                        if (betterSolution(allNonDominatedSolutions, &paretoFrontIA[j], alteredSolution) == 1){
                            paretoFrontIA[j].amountVertices = alteredSolution->amountVertices;
                            paretoFrontIA[j].depotPosition = alteredSolution->depotPosition;
                            paretoFrontIA[j].totalLatency = alteredSolution->totalLatency;
                            paretoFrontIA[j].totalProfit = alteredSolution->totalProfit;
                            paretoFrontIA[j].travelCost = alteredSolution->travelCost;

                            paretoFrontIA[j].vertices = malloc(alteredSolution->amountVertices * sizeof(Vertice));

                            for (int k = 0; k < alteredSolution->amountVertices; k++){
                                paretoFrontIA[j].vertices[k] = alteredSolution->vertices[k];
                            }
                        }

                        onlyAddNonDominatedSolutions(allNonDominatedSolutions, alteredSolution);

                        updatePosterioriSolutions(posterioriSolutionsInformation, alteredSolution);

                        free(alteredSolution->vertices);
                        free(alteredSolution);
                        break;
                    default:
                        break;
                }
            }
        }

        iterationCounter++;
    }

    end = clock();

    FILE *outfile4 = fopen("2.1 ValoresCustoViajemSoluçõesFinais.in", "w");
    if (outfile4 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    FILE *outfile5 = fopen("2.2 ValoresLatênciaSoluçõesFinais.in", "w");
    if (outfile5 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    FILE *outfile6 = fopen("2.3 ValoresLucroSoluçõesFinais.in", "w");
    if (outfile6 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    FILE *outfile7 = fopen("2.4 QuantidadeClientesSoluçõesFinais.in", "w");
    if (outfile7 == NULL) {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    for (NodeSolution *node = allNonDominatedSolutions->head; node != NULL; node = node->next) {
        fprintf(outfile4, "%.2lf\n", node->solution->travelCost);
        fprintf(outfile5, "%.2lf\n", node->solution->totalLatency);
        fprintf(outfile6, "%d\n", node->solution->totalProfit);
        fprintf(outfile7, "%d\n", node->solution->amountVertices);
    }

    fclose(outfile4);
    fclose(outfile5);
    fclose(outfile6);
    fclose(outfile7);

    cpuTimeUsed = ((double) (end - start - (pauseEnd - pauseStart))) / CLOCKS_PER_SEC;
    printf("Algoritmo transgenetico levou %f segundos para executar \n", cpuTimeUsed);
}




int main() {
    srand(time(0));

    FILE *file = fopen("Y-berlin52.in", "r");
    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }

    int numVertices;
    fscanf(file, "%d", &numVertices);

    Vertice *allVertices = malloc(numVertices * sizeof(Vertice));
    for (int i = 0; i < numVertices; i++) {
        fscanf(file, "%d %lf %lf %d", &allVertices[i].identification, &allVertices[i].coordinateX, &allVertices[i].coordinateY, &allVertices[i].profit);
    }

    fclose(file);

    int alphaPicked = chooseAplhaValue();
    int gamaPicked = chooseGamaValue();
    double alpha = assignAlphaValue(alphaPicked);
    double gama = assignGamaValue(gamaPicked);

    transgeneticMainLoop(allVertices, numVertices, alpha, gama);

    return 0;
}
