from recompute_pointer_table import parsePointerTables, dumpPointerTableDetails

newROMName = "./rom/dk64_kiosk.z64"

with open(newROMName, "rb") as fh:
    parsePointerTables(fh)
    dumpPointerTableDetails("rom/pointer_tables_vanilla.log", fh)