
/***************************************************************************/ /**
  @file     file_system_manager.c
  @brief    File System functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#include <file_system_manager.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_ARRAY_SIZE	200

/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

Mp3File_t files [FILE_ARRAY_SIZE] = {};
int filesCount = 0;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

bool FileSystem_isMp3File(char * path)
{
    char *extension;
    if ((extension = strrchr(path, '.')) != NULL)
    {
        if (strcmp(extension, ".mp3") == 0)
        {
            return true;
        }
    }
    return false;
}

void FileSystem_AddFile(char * path)
{
	Mp3File_t * newFile = &files[filesCount];
	strcpy(newFile->path, path);
	newFile->index = filesCount;
	filesCount++;
}

Mp3File_t FileSystem_GetFirstFile(void)
{
	if (filesCount == 0)
	{
		Mp3File_t nullFile = {.index = -1, .path = ""};
		return nullFile;
	}
	return files[0];
}

Mp3File_t FileSystem_GetNextFile(Mp3File_t currentFile)
{
	int nextFileIndex = currentFile.index + 1;
	if(currentFile.index == filesCount)
	{
		nextFileIndex = 0;
	}
	return files[nextFileIndex];
}

Mp3File_t FileSystem_GetPreviousFile(Mp3File_t currentFile)
{
	int previousFileIndex = currentFile.index - 1;
	if(currentFile.index == 0)
	{
		previousFileIndex = filesCount - 1;
	}
	return files[previousFileIndex];
}

char * FileSystem_GetFileName(Mp3File_t file)
{
	char str[STR_SIZE];
	strcpy(str, file.path);
	char *pch;
	pch = strtok(str, "/");
	char fileNamePart[STR_SIZE];
	while (pch != NULL)
	{
		//printf("%s\n", pch);
		strcpy(fileNamePart, pch);
		pch = strtok(NULL, "/");
	}
	char * fileName;
	fileName = strtok(fileNamePart, ".");
	return fileName;
}

void FileSystem_Test (void)
{
	 /*TEST*/
	char *filename = "/dir0/hola.mp3";
	char *filename2 = "/dir0/hola2.mp3";
	char *filename3 = "/dir1/hola3.mp3";
	char *filename4 = "/dir1/hola4.mp3";
	char *filename5 = "/dir2/hola5.mp3";
	FileSystem_AddFile(filename);
	FileSystem_AddFile(filename2);
	FileSystem_AddFile(filename3);
	FileSystem_AddFile(filename4);
	FileSystem_AddFile(filename5);

	/* Test File Addition & Test Get File Name */
	for (int i = 0; i< filesCount; i++)
	{
		printf("File n%d path: %s\n", i ,files[i].path);
		char * fileName = FileSystem_GetFileName(files[i]);
		printf("File n%d name: %s\n", i ,fileName);
	}

	/* Test Mp3 Recognition */
	if (FileSystem_isMp3File("/dir0/archivo0.mp3"))
		printf("archivo0 es mp3\n");
	if (FileSystem_isMp3File("/dir0/archivo1.xls"))
		printf("archivo1 es mp3\n");
	if (FileSystem_isMp3File("/dir0"))
		printf("dir0 es mp3\n");

	/* Test Get First File */
	Mp3File_t currentFile = FileSystem_GetFirstFile();
	printf("Primer Archivo: %s\n", currentFile.path);

	/*Test File System Navigation*/
	for (int j = 0 ; j<2; j++)
	{
		currentFile = FileSystem_GetNextFile(currentFile);
		printf("Archivo Siguiente: %s\n", currentFile.path);
	}

	for (int k = 0; k<2; k++)
	{
		currentFile = FileSystem_GetPreviousFile(currentFile);
		printf("Anterior Archivo: %s\n", currentFile.path);
	}

	/*Test File System Overflow*/
	currentFile = FileSystem_GetFirstFile();
	printf("Index: %d\n", currentFile.index);
	for (int l = 0 ; l<10; l++)
	{
		currentFile = FileSystem_GetNextFile(currentFile);
		printf("Index Siguiente: %d\n", currentFile.index);
	}
	for (int m = 0; m<2; m++)
	{
		currentFile = FileSystem_GetPreviousFile(currentFile);
		printf("Index Anterior: %s\n", currentFile.index);
	}

}

