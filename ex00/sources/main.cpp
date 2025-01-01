/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytop <ytop@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 18:55:31 by ytop              #+#    #+#             */
/*   Updated: 2025/01/01 19:21:01 by ytop             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main()
{
    Zombie  *zombie;

    zombie = newZombie("Heap");
    zombie->announce();
    delete(zombie);

    randomChup("Stack Zombie");
    return (0);
}
