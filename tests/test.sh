#! /bin/bash

t_list *lst;
	// sh_asterisk ("/home/ksorokol/43_team/minishell/*e/*");
	lst = sh_asterisk ("~/*43*/*mini*/../mini*/*");
	ft_lstiter (lst, &list_print);
	ft_lstclear (&lst, a_split_clear);
	printf ("--->\n");
	lst = sh_asterisk (argv[1]);
	ft_lstiter (lst, &list_print);
	ft_lstclear (&lst, a_split_clear);
	return (EXIT_SUCCESS);

	t_list *lst;
	// sh_asterisk ("/home/ksorokol/43_team/minishell/*e/*");
	// lst = sh_asterisk ("~/*42*/*mini*/../mini*/*");
	// lst = sh_asterisk (sh_replace_tilde ("~/././././././*"));
	// lst = sh_asterisk (sh_replace_tilde ("/home/./*/./././*"));
	lst = sh_asterisk (sh_replace_tilde ("/r*/./*/./././*"));
	ft_lstiter (lst, &list_print);
	ft_lstclear (&lst, a_split_clear);
	if (argc == 2)
	{
		lst = sh_asterisk (argv[1]);
		ft_lstiter (lst, &list_print);
		ft_lstclear (&lst, a_split_clear);
	}
	return (EXIT_SUCCESS);