
/***************************************************************************/ /**
  @file     file_system_manager.c
  @brief    File System functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <file_system_manager_old.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NODE_ARRAY_SIZE	200
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static TREE_NODE_T *createNode(char *completeUrl, char *nodeName, TREE_NODE_T *parentNode, TREE_NODE_T *leftSibling);
static TREE_NODE_T *accessNode(char *url, TREE_NODE_T *parentNode);

/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
TREE_NODE_T rootNode = {.url = "", .nodeName = ""};

TREE_NODE_T  nodes [NODE_ARRAY_SIZE] = {};
int nodeCount = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

TREE_NODE_T *getRootNode()
{
    return &rootNode;
}

bool isMp3File(char *url)
{
    char *ext;
    if ((ext = strrchr(url, '.')) != NULL)
    {
        if (strcmp(ext, ".mp3") == 0)
        {
            return true;
        }
    }
    return false;
}

void testFileTree()
{
    /*TEST*/
    char *filename = "/dir0/hola.mp3";
    char *filename2 = "/dir0/hola2.mp3";
    char *filename3 = "/dir1/hola3.mp3";
    char *filename4 = "/dir1/hola4.mp3";
    char *filename5 = "/dir2/hola5.mp3";
    addFileToTree(filename);
    addFileToTree(filename2);
    addFileToTree(filename3);
    addFileToTree(filename4);
    addFileToTree(filename5);
    printCompleteFileTree(true);
    if (isMp3File("/dir0/archivo0.mp3"))
		printf("archivo0 es mp3");
	if (isMp3File("/dir0/archivo1.xls"))
		printf("archivo1 es mp3");
	if (isMp3File("/dir0"))
		printf("dir0 es mp3");
}

void addFileToTree(char *url)
{
    char str[STR_SIZE];
    strcpy(str, url);
    char *pch;
    pch = strtok(str, "/");
    TREE_NODE_T *parentNode = &rootNode;
    while (pch != NULL)
    {
        //printf("%s\n", pch);
        char path[STR_SIZE];
        strcpy(path, pch);
        parentNode = accessNode(path, parentNode);
        pch = strtok(NULL, "/");
    }
}
void printTree(TREE_NODE_T *parentNode, char *spacing, bool printCompleteUrl)
{
    char printableUrl[STR_SIZE];
    strcpy(printableUrl, spacing);
    if (printCompleteUrl)
    {
        strcat(printableUrl, parentNode->url);
    }
    else
    {
        strcat(printableUrl, parentNode->nodeName);
    }

    printf(printableUrl);
    printf("\n");
    if (parentNode->childNode != NULL)
    {
        char newSpacing[STR_SIZE];
        strcpy(newSpacing, spacing);
        strcat(newSpacing, "**");
        printTree(parentNode->childNode, newSpacing, printCompleteUrl);
    }
    if (parentNode->rightSiblingNode != NULL)
    {
        printTree(parentNode->rightSiblingNode, spacing, printCompleteUrl);
    }
}

void printCompleteFileTree(bool printCompleteUrl){
	printTree(&rootNode, "" , printCompleteUrl);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static TREE_NODE_T *accessNode(char *url, TREE_NODE_T *parentNode)
{
    TREE_NODE_T *childNode = parentNode->childNode;
    char completeUrl[STR_SIZE];
    strcpy(completeUrl, parentNode->url);

    strcat(completeUrl, "/");
    strcat(completeUrl, url);

    if (childNode != NULL)
    {
        if (strcmp(childNode->url, completeUrl) == 0)
        {
            return childNode;
        }

        while (childNode->rightSiblingNode != NULL)
        {
            childNode = childNode->rightSiblingNode;

            if (strcmp(childNode->url, completeUrl) == 0)
            {
                return childNode;
            }
        }
    }

    return createNode(completeUrl, url, parentNode, childNode);
}

static TREE_NODE_T *createNode(char *completeUrl, char *nodeName, TREE_NODE_T *parentNode, TREE_NODE_T *leftSibling)
{
	nodeCount++;
    if (leftSibling == NULL)
    {
        //FIRST CHILD
    	TREE_NODE_T * node = &nodes[nodeCount];
        strcpy(node->url, completeUrl);
        strcpy(node->nodeName, nodeName);
        node->parentNode = parentNode;
        parentNode->childNode = node;
        return node;
    }
    else
    {
        //ADD SIBLING
    	TREE_NODE_T *node = &nodes[nodeCount];
        strcpy(node->url, completeUrl);
        strcpy(node->nodeName, nodeName);
        node->parentNode = parentNode;
        node->leftSiblingNode = leftSibling;
        leftSibling->rightSiblingNode = node;
        return node;
    }

}


