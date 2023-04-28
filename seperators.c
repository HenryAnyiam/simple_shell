#include "main.h"

/**
  *handle_sep - handles command seperators
  *@cmd: struct holding important data
  *)
  *Return: 0 or -1
  */
int handle_sep(cmd_in *cmd)
{
	cmd_list *head_c, *end_c;
	sep_list *head_s, *end_s;
	int check, i = 0;

	head_c = NULL;
	head_s = NULL;
	add_input(&head_c, cmd->cmd);
	add_sep(&head_s, cmd->cmd);
	end_c = head_c;
	end_s = head_s;
	while (end_c != NULL)
	{
		if (i != 0)
			free_cmd(cmd->args);
		cmd->args = set_args(end_c->cmd);
		check_args(cmd);
		check = handle_cmd(cmd);
		if (check == -1)
			break;
		next_cmd(cmd, &end_c, &end_s);
		if (end_c != NULL)
			end_c = end_c->next;
		++i;
	}
	free_sp(head_s);
	free_in(head_c);
	return (check);
}

/**
  *add_input - breaks string according to seperators, add to node
  *@head_c: pointer to first node
  *@str: command input
  *)
  *Return: first node
  */
cmd_list *add_input(cmd_list **head_c, char *str)
{
	char *hold, *temp;
	char *dup = _strdup(str);

	hold = _strtok(dup, ";&|");
	temp = _strdup(hold);
	cmd_node(head_c, temp);
	while (hold != NULL)
	{
		hold = _strtok(NULL, ";&|");
		if (hold != NULL)
		{
			if (hold[0] == '\0')
				hold = _strtok(NULL, ";&|");
			temp = _strdup(hold);
			cmd_node(head_c, temp);
		}
	}
	free(dup);
	return (*head_c);
}

/**
  *add_sep - gets seperator and sends to node
  *@head: pointer to first node
  *@str: command input
  *)
  *Return: first node
  */
sep_list *add_sep(sep_list **head, char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] == '&') && (str[i + 1] == '&'))
		{
			sep_node(head, '&');
			i++;
		}
		else if ((str[i] == '|') && (str[i + 1] == '|'))
		{
			sep_node(head, '|');
			i++;
		}
		else if (str[i] == ';')
		{
			sep_node(head, ';');
		}
	}
	return (*head);
}

/**
  *next_cmd - gets next command to exec according to seperators
  *@cmd: struct holding important data
  *@in_head: node to current command
  *@sp_head: node to current seperators
  */
void next_cmd(cmd_in *cmd, cmd_list **in_head, sep_list **sp_head)
{
	sep_list *s_temp;
	cmd_list *c_temp;
	int check = 1;

	s_temp = *sp_head;
	c_temp = *in_head;
	while ((s_temp != NULL) && (check != 0))
	{
		if (cmd->status == 0)
		{
			if ((s_temp->sep == '&') || (s_temp->sep == ';'))
				check = 0;
			else if (s_temp->sep == '|')
			{
				c_temp = c_temp->next;
				s_temp = s_temp->next;
			}
		}
		else
		{
			if ((s_temp->sep == '|') || (s_temp->sep == ';'))
				check = 0;
			else if (s_temp->sep == '&')
			{
				c_temp = c_temp->next;
				s_temp = s_temp->next;
			}
		}
		if ((s_temp != NULL) && (check == 0))
			s_temp = s_temp->next;
	}
	*sp_head = s_temp;
	*in_head = c_temp;
}
