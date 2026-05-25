-) Per selezionare la parte (prima / seconda) dell'esercitazione cambiare la costante PARTE definita nel fiel main_draft.cpp
-) Per generare correttamente la documentazione doxygen a partire dai file sorgente eseguire le seguenti operazione aggiuntive:
	1) Aggiungere sotto Expert/Input la costante ".tpp" a FILE_PATTERNS
	2) Aggiungere sotto Expert/Project la costante "tpp=C++" a EXTENSION_MAPPING
-) Per compilare correttamente il codice è necessario usare almeno la versione std:c++20 o più recente. Nel caso si volesse usare la versione std:c++17 sostituire i file con quelli nella cartella cpp17 dovrebbe permettere la compilazioen anche con la versione più vecchia (non particolarmente testato).