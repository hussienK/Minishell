# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkanaan <hkanaan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 13:39:35 by mokhan            #+#    #+#              #
#    Updated: 2024/06/15 17:37:34 by hkanaan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define variables
TARGET = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
RM = rm -f
INCLUDE_DIR = -I includes

# Source and object file lists
SOURCE_FILES =	src/ft_printf \
		src/ft_printf_utils \
		src/ft_printf_utils_ptr \
		src/ft_printf_utils_extra \
		src/ft_printf_utils_complicated \

SOURCES = $(addsuffix .c, $(SOURCE_FILES))
OBJECTS = $(addsuffix .o, $(SOURCE_FILES))

# Build rules

$(TARGET): $(OBJECTS)
	@ $(AR) $(TARGET) $(OBJECTS)

%.o: %.c
	@ $(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

all: $(TARGET)

clean:
	@ $(RM) -rf $(OBJECTS)

fclean: clean
	@ $(RM) $(TARGET)

bonus: all

re: fclean all