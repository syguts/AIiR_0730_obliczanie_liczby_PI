from PI2.models import Task, DoneTask
import PI2
from django.template import Context, loader
from django.shortcuts import render
from django.shortcuts import render_to_response
from django.utils import timezone
from django.template import RequestContext
from PI2.forms import UserForm, CommisionTask
from django.contrib.auth import authenticate, login
from django.http import HttpResponseRedirect, HttpResponse
from django.contrib.auth.decorators import login_required
from django.contrib.auth import logout
from .forms import CommisionTask
    from django.http import HttpResponse
from datetime import date
import parser
from django.forms.fields import DateTimeField

def index(request):
    
    form = CommisionTask(request.POST)
        if form.is_valid():
            Task = form.save(commit=False)
            Task.userID = request.user
            Task.save()
            
            #Resetuje formularz po pobraniu poprawnym
            form =CommisionTask(0);
    
    return render_to_response('index.html', {'form': form }, context_instance=RequestContext(request))

def wyczysc(request):
    
    Task.objects.all().delete()
    DoneTask.objects.all().delete()
    
    return HttpResponse('Czyszczenie bazy wykonane!')

def odswiez(request):
    
    """Tutaj mamy pobieranie danych z tabeli i przekazywanie do strony. Pobieramy wszystkie dane z tabeli task czyli .all()
        filtrujemy po userID = ID   oraz sortujemy po dacie dodania malejaco od najmlodszego czyli descending a odpowiada za to:
        minus myslnik - przed fieldem czyli rekordem add_date"""
    form2 = PI2.models.DoneTask.objects.all().filter(userID= request.user.id).order_by('-add_date')
    
    return render_to_response('odswiez.html', {'form2': form2}, context_instance=RequestContext(request))

...