#include "main.h"

int handle_sep(cmd_in *cmd)
{
	cmd_list *head_c, *end_c;
	sep_list *head_s, *end_s;
	int check;

	head_c = NULL;
	head_s = NULL;
	add_input(&head_c, cmd->cmd);
	add_sep(&head_s, cmd->cmd);
	end_c = head_c;
	end_s = head_s;
	while (end_c != NULL)
	{
		cmd->args = set_args(end_c->cmd);
		check_args(cmd);
		check = handle_cmd(cmd);
		if (check == -1)
			break;
		next_cmd(cmd, &end_c, &end_s);
		if (end_c != NULL)
			end_c = end_c->next;
	}
	free_sp(&head_s);
	free_in(&head_c);
	return (check);
}

cmd_list *add_input(cmd_list **head_c, char *str)
{
	char *hold, *temp;
	char *dup = _strdup(str);

	hold = _strtok(dup, ";|&");
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

sep_list *add_sep(sep_list **head, char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '&')
		{
			sep_node(head, '&');
			i++;
		}
		else if (str[i] == '|')
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
