#include "main.h"

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

void free_in(cmd_list **head)
{
	cmd_list *temp;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->cmd);
		free(*head);
		*head = temp;
	}
}

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

void free_sp(sep_list **head)
{
	sep_list *temp;

	while (*head)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
}
