#include "lbg_global.h"

#include <stdio.h>
#include <string.h>

Command CommandList;

void InitCommandList()
{
	CommandList.cmd = 0;
	CommandList.before = 0;
	CommandList.next = 0;
}

void AddNode(char *cmd)
{
	Command* newNode = (Command *)malloc(sizeof(Command));

	newNode->cmd = (char*)malloc(strlen(cmd) + 1);
	strcpy(newNode->cmd, cmd);

	newNode->before = &CommandList;
	newNode->next = CommandList.next;

	CommandList.next->before = newNode;
	CommandList.next = newNode;
}

void FreeNode(Command *node)
{
	if (node == 0)
		return;

	node->before = 0;
	node->next = 0;

	if (node->cmd)
		free(node->cmd);
}

int GetListLen()
{
	int len = 0;
	Command* cur = CommandList.next;

	while (cur)
	{
		++len;
		cur = cur->next;
	}

	return len;
}

Command *TakeFirstNode()
{
	// take first node
	Command *firstNode = CommandList.next;

	if (firstNode != 0)
	{
		// unlink the first node
		if (CommandList.next->next)	CommandList.next->next->before = &CommandList;
		CommandList.next = CommandList.next->next;
	}

	return firstNode;
}

Command *TakeNodeAt(int index)
{
	Command *cur = CommandList.next;
	int curPos = 0;

	while (cur->next && curPos <= index)
	{
		if (curPos == index)
			break;

		cur = cur->next;
		++curPos;
	}

	if (curPos == index)
		return cur;

	return 0;
}

int FindNode(char *cmd)
{
	Command* cur = CommandList.next;
	int curPos = 0;

	while (cur)
	{
		if (!strcmp(cmd, cur->cmd))
			return curPos;

		cur = cur->next;
		++curPos;
	}

	return 0;
}

void AddCommand(char* cmd)
{
	AddNode(cmd);
}

char *GetFirstCommand()
{
	// take the first node
	Command *firstNode = TakeFirstNode();

	// copy command
	char* cmd = (char*)malloc(strlen(firstNode->cmd) + 1);
	strcpy(cmd, firstNode->cmd);

	// destroy node
	FreeNode(firstNode);

	return cmd;
}