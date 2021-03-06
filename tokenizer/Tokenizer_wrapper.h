/*---------------------------------------------------------------------------------------------
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Licensed under the MIT License. See License.txt in the project root for license information.
*--------------------------------------------------------------------------------------------*/
#pragma once
#define CALL_CONV

using PFN_LoadTokenizer = void*(CALL_CONV *)();
using PFN_LoadDefaultConfig = void(CALL_CONV*)(void* tokenizer, int config_type);
using PFN_UnloadTokenizer = void(CALL_CONV*)(void* tokenizer);
using PFN_TokenizeString = void*(CALL_CONV *)(void* tokenizer, const char* czInput, bool translit);
using PFN_NextToken = void*(CALL_CONV *)(void* result, int* start, int* len, int* type);
using PFN_FreeTokenizedResult = void(CALL_CONV *)(void* result);