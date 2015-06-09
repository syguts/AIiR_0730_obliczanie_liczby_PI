class CommisionTask(forms.ModelForm):
    numberOfPoints = forms.IntegerField(label ="", min_value=1)
    numberOfThreads = forms.IntegerField(label ="", max_value=12, min_value=1)
    
    class Meta:
        model = Task
        fields = ('numberOfPoints', 'numberOfThreads' )