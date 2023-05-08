// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigReader.h"

TMap<FString, FString> UConfigReader::ReadConfig(FString path) {
	TMap<FString, FString> cfg;

	TArray<FString> configLines;

	const TCHAR* Cpath = *path;
	if (!FFileHelper::LoadANSITextFileToStrings(Cpath, NULL, configLines)) {
		return cfg;
	}

	for (FString string : configLines) {
		if (string != "") {
			TArray<FString> buf;
			string.ParseIntoArray(buf, TEXT("="), true);
			cfg.Add(buf[0], buf[1]);
		}
	}
	return cfg;
};