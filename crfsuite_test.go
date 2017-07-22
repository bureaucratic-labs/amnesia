package crfsuite

import (
	"fmt"
	"reflect"
	"strings"
	"testing"
)

func features(items []string, position int) []Feature {
	result := make([]Feature, 0)
	result = append(result, Feature{
		Key:   fmt.Sprintf("lower=%v", strings.ToLower(items[position])),
		Value: 1.0,
	})
	return result
}

func TestModelFromFile(t *testing.T) {
	model := NewModelFromFile("test_data/tokenization-model.crfsuite")
	labels := model.Labels
	if labels.Length() != 3 {
		t.Fail()
	}
	label := labels.ToString(0)
	if label != "B" {
		t.Fail()
	}
}

func TestTagger(t *testing.T) {
	model := NewModelFromFile("test_data/tokenization-model.crfsuite")
	tagger := model.GetTagger()
	items := []string{"т", "е", "с", "т", "."}
	result := tagger.Tag(items, features)
	gold := []int{1, 1, 1, 1, 0} // equals to IIIO
	if !reflect.DeepEqual(result, gold) {
		t.Fail()
	}
}

func BenchmarkTagger(b *testing.B) {
	model := NewModelFromFile("test_data/tokenization-model.crfsuite")
	tagger := model.GetTagger()
	items := []string{"т", "е", "с", "т", "."}
	for i := 0; i < b.N; i++ {
		tagger.Tag(items, features)
	}
}
