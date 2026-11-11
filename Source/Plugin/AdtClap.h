// AdtClap.h
// The three entry functions clap-wrapper links into every format.

#pragma once

bool tbadt_entry_init (const char* pluginPath);
void tbadt_entry_deinit();
const void* tbadt_entry_get_factory (const char* factoryId);
