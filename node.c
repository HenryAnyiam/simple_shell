#include "main.h"

/**
  *cmd_node - adds node to end of list
  *@head: pointer to first node
  *@str: command string to add
  *)
  *Return: first node pointer
  */
cmd_list *cmd_node(cmd_list **head, char *str)
{
	cmd_list *new, *temp;

	new = malloc(sizeof(cmd_list));
	if (new == NULL)
	{
		write(STDERR_FILENO, "Allocation Error\n", 18);
		return (NULL);
	}
	new->cmd = str;
	new->next = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = new;
		return (*head);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (*head);
}

/**
  *free_in - free node
  *@head: pointer to first node
  */
void free_in(cmd_list *head)
{
	cmd_list *temp;

	while (head)
	{
		temp = head->next;
		free(head->cmd);
		free(head);
		head = temp;
	}
}

/**
  *sep_node - add node to end of seperators list
  *@head: pointer to first node
  *@c: seperator
  *)
  *Return: first node
  */
sep_list *sep_node(sep_list **head, char c)
{
	sep_list *new, *end;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
	{
		write(STDERR_FILENO, "Allocation Error\n", 18);
		return (NULL);
	}
	new->sep = c;
	new->next = NULL;
	end = *head;
	if (end == NULL)
	{
		(*head) = new;
		return (*head);
	}
	while (end->next != NULL)
		end = end->next;
	end->next = new;
	return (*head);
}

/**
  *free_sp - free linked list
  *@head: pointer to first node
  */
void free_sp(sep_list *head)
{
	sep_list *temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
