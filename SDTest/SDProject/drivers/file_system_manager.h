/***************************************************************************/ /**
  @file     file_system_manager.h
  @brief    File System header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef FYLE_SYSTEM_MANAGER_H
#define FYLE_SYSTEM_MANAGER_H


#include <stdbool.h>
#define STR_SIZE	255
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

typedef struct TREE_NODE_T TREE_NODE_T;
struct TREE_NODE_T
{

    TREE_NODE_T *parentNode;
    TREE_NODE_T *childNode;
    TREE_NODE_T *rightSiblingNode;
    TREE_NODE_T *leftSiblingNode;
    char url[STR_SIZE];
    char nodeName[STR_SIZE];
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void testFileTree();
void addFileToTree(char *url);
bool isMp3File(char *url);

TREE_NODE_T *getRootNode();
void printCompleteFileTree(bool printCompleteUrl);
void printTree(TREE_NODE_T *parentNode, char *spacing, bool printCompleteUrl);
#endif /*FYLE_SYSTEM_MANAGER_H*/