TEST FOR SHELL


signal(SIGSEGV, &handle_signal);

signal(SIGTERM, &handle_signal);

signal(SIGQUIT, &handle_signal);

signal(SIGINT, &handle_signal);
