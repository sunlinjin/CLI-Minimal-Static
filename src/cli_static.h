/**
 * Copyright 2019 Sander van der Meulen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
 * of the Software, and to permit persons to whom the Software is furnished to do 
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Minimalistic Static CLI for embedded devices
 * 
 * Author: Sander van der Meulen
 * 
 */

#ifndef CLI_STATIC_H_
#define CLI_STATIC_H_

#include <stdint.h>

////////////////////////////////////////////////////
// application specific
#include <stdio.h>
#define CLI_PRINTF		printf
////////////////////////////////////////////////////

#ifndef CLI_PRINTF
	#define CLI_PRINTF(fmt)
#endif

// function pointer typedef
typedef void (*command_line_callback_f)(char *command_str);

// command structure
typedef struct {
	// The command that causes the command interperter to be executed.
	// For example "help".  Must be all lower case.
	const char *command_str;
	// String that describes how to use the command.  Should start with
	// the command itself, and end with "\r\n".
	const char *help_str;
	// A pointer to the callback function that will return the output
	// generated by the command.
	const command_line_callback_f command_callback;
	// Commands expect a fixed number of parameters, which may be zero.
	uint8_t parameter_count;
} cli_command_definition_t;

/**
 * @brief Process incomming serial data string
 *
 * This funciton processes a serial data string which is
 * given as a parameter. The string should not contain odd
 * characters like new lines and carriage return characters.
 * the function will search through all known commands which are 
 * found inside the cli_static_cmd.c file. If the command is found,
 * it is executed. If errors occure during the parsing of the command
 * or the number of parameters is incorrect, a error messege will
 * be written using CLI_PUTS().
 * 
 * @param received_command_str The string to process
 * 
 * @return OK (0) or Error (-1)
 */
extern int cli_process_command(char *received_command_str);

/**
 * @brief Get the specified parameter from a string
 *
 * This function will search through the given string for
 * the specified parameter. The parameters should be split
 * using spaces and may not contain spaces themselves.
 * a char pointer to the start of the parameter is returned.
 * 
 * @param command_string The string to search through
 * @param wanted_parameter The integer number of the wanted parameter
 * @param parameter_str_len A pointer which will contian the 
 * parameter length when returned
 * 
 * @return OK (valid pointer) or Error (NULL pointer)
 */
extern char *cli_get_parameter(char *command_string, int wanted_parameter, int *parameter_str_len);

#endif // CLI_STATIC_H_
