#pragma once
void init_platform_specific(void);
void abort_example(char const* format, ...);
void open_log(void);
void open_log_monospace(void);
void close_log(bool wait_for_user);
void log_printf(char const* format, ...);

