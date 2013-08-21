BEGIN{
	in_entity = 0;
	after_comment = 0;
}

/\/\*QUAKED/ && in_entity == 0 {
	in_entity = 1;
	after_comment = 0;
}
/\*\// && in_entity == 1 {
	print $0 "\n"
	in_entity = 0;
	after_comment = 1;
}

after_comment == 0 && in_entity == 1 {
	print $0
}

after_comment == 1 && /}/ {
	after_comment = 0
}

