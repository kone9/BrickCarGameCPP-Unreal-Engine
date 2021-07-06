// Fill out your copyright notice in the Description page of Project Settings.


#include "ReglasJuego.h"
#include "..\Public\ReglasJuego.h"

bool AReglasJuego::IfLose()
{
	if (lose == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AReglasJuego::IFGameOver()
{
	if (gameOver == false)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}
