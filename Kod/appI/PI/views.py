from django.template import Context, loader
from django.shortcuts import render

from django.http import HttpResponse
from PI.models import Task

def index(request):
    latest_PI_list = Task.objects.all().order_by('-add_date')[:5]
    t = loader.get_template('index.html')
    c = Context({
        'latest_PI_list': latest_PI_list,
    })
    return HttpResponse(t.render(c))

def detail(request, PI_id):
    return HttpResponse("You're looking at PI %s." % PI_id)

def results(request, PI_id):
    return HttpResponse("You're looking at the results of PI %s." % PI_id)

def vote(request, PI_id):
    return HttpResponse("You're voting on PI %s." % PI_id)
