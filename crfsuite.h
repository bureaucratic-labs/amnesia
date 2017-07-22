#include "crfsuite/include/crfsuite.h"

crfsuite_model_t* NewModelFromFile(char* path) {
    crfsuite_model_t* model = NULL;
    int ret = crfsuite_create_instance_from_file(path, (void**)&model);
    return model;
}

crfsuite_dictionary_t* GetModelLabels(crfsuite_model_t* model) {
    crfsuite_dictionary_t* labels = NULL;
    int ret = model->get_labels(model, &labels);
    return labels;
}


crfsuite_dictionary_t* GetModelAttributes(crfsuite_model_t* model) {
    crfsuite_dictionary_t* attributes = NULL;
    int ret = model->get_attrs(model, &attributes);
    return attributes;
}

crfsuite_tagger_t* GetModelTagger(crfsuite_model_t* model) {
    crfsuite_tagger_t *tagger = NULL;
    int ret = model->get_tagger(model, &tagger);
    return tagger;
}

int DictionaryLength(crfsuite_dictionary_t* dictionary) {
    return dictionary->num(dictionary);
}

int DictionaryGet(crfsuite_dictionary_t* dictionary, const char *str) {
    return dictionary->get(dictionary, str);
}

int DictionaryToID(crfsuite_dictionary_t* dictionary, const char *str) {
    return dictionary->to_id(dictionary, str);
}

char* DictionaryToString(crfsuite_dictionary_t* dictionary, int id) {
    const char *str = NULL;
    dictionary->to_string(dictionary, id, &str);
    return (char*)str;
}

void DictionaryFree(crfsuite_dictionary_t* dictionary, char* str) {
    dictionary->free(dictionary, str);
}

crfsuite_attribute_t NewAttribute(int id, float value) {
    crfsuite_attribute_t cont;
    crfsuite_attribute_set(&cont, id, value);
    return cont;    
}

crfsuite_item_t NewItem() {
    crfsuite_item_t item;
    crfsuite_item_init(&item);
    return item;
}

int AppendAttributeToItem(void* item, void* attr) {
    return crfsuite_item_append_attribute(item, attr);
}

crfsuite_instance_t NewInstance() {
    crfsuite_instance_t inst;
    crfsuite_instance_init(&inst);
    return inst;
}

int EmptyInstance(void* inst) {
    return crfsuite_instance_empty(inst);
}

int AddItemToInstance(void* inst, void* item, int label_id) {
    crfsuite_instance_append(inst, item, label_id);
    crfsuite_item_finish(item);
}

int InstanceLength(void* inst) {
    return ((crfsuite_instance_t*)(inst))->num_items;
}

int InstanceFinish(void* inst) {
    crfsuite_instance_finish(inst);
}

int SetTaggerInstance(crfsuite_tagger_t* tagger, void* inst) {
    tagger->set(tagger, inst);
}

int* TaggerDecode(crfsuite_tagger_t* tagger, int length) {
    floatval_t score = 0;
    int *output = calloc(sizeof(int), length);
    tagger->viterbi(tagger, output, &score);
    return output;
}

