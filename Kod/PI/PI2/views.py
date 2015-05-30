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


def odswiez2(request):
    
    """Tutaj mamy pobieranie danych z tabeli i przekazywanie do strony. Pobieramy wszystkie dane z tabeli task czyli .all()
    filtrujemy po userID = ID   oraz sortujemy po dacie dodania malejaco od najmlodszego czyli descending a odpowiada za to:
     minus myslnik - przed fieldem czyli rekordem add_date""" 
    form3 = PI2.models.Task.objects.all().filter(userID= request.user.id).order_by('-add_date')
    
    return render_to_response('odswiez2.html', {'form3': form3}, context_instance=RequestContext(request))


    
def register(request):

    # A boolean value for telling the template whether the registration was successful.
    # Set to False initially. Code changes value to True when registration succeeds.
    registered = False

    # If it's a HTTP POST, we're interested in processing form data.
    if request.method == 'POST':
        # Attempt to grab information from the raw form information.
        # Note that we make use of both UserForm and UserProfileForm.
        user_form = UserForm(data=request.POST)


        # If the two forms are valid...
        if user_form.is_valid(): #and profile_form.is_valid():
            # Save the user's form data to the database.
            user = user_form.save()

            # Now we hash the password with the set_password method.
            # Once hashed, we can update the user object.
            user.set_password(user.password)
            user.save()



            # Update our variable to tell the template registration was successful.
            registered = True

        # Invalid form or forms - mistakes or something else?
        # Print problems to the terminal.
        # They'll also be shown to the user.
        else:
            print user_form.errors
            return render(request, 'unavailable_login.html', {})

    # Not a HTTP POST, so we render our form using two ModelForm instances.
    # These forms will be blank, ready for user input.
    else:
        user_form = UserForm()


    # Render the template depending on the context.
    return render(request,
            'register.html',
            {'user_form': user_form, 'registered': registered} )

@login_required
def restricted(request):
    return HttpResponse("Since you're logged in, you can see this text!")

def user_login(request):

    # If the request is a HTTP POST, try to pull out the relevant information.
    if request.method == 'POST':
        # Gather the username and password provided by the user.
        # This information is obtained from the login form.
                # We use request.POST.get('<variable>') as opposed to request.POST['<variable>'],
                # because the request.POST.get('<variable>') returns None, if the value does not exist,
                # while the request.POST['<variable>'] will raise key error exception
        username = request.POST.get('username')
        password = request.POST.get('password')

        # Use Django's machinery to attempt to see if the username/password
        # combination is valid - a User object is returned if it is.
        user = authenticate(username=username, password=password)

        # If we have a User object, the details are correct.
        # If None (Python's way of representing the absence of a value), no user
        # with matching credentials was found.
        if user:
            # Is the account active? It could have been disabled.
            if user.is_active:
                # If the account is valid and active, we can log the user in.
                # We'll send the user back to the homepage.
                login(request, user)
                return HttpResponseRedirect('/')
            else:
                # An inactive account was used - no logging in!
                return HttpResponse("Your account is disabled.")
        else:
            # Bad login details were provided. So we can't log the user in.
            print "Invalid login details: {0}, {1}".format(username, password) 
            return render(request, 'invalid_login.html', {})

    # The request is not a HTTP POST, so display the login form.
    # This scenario would most likely be a HTTP GET.
    else:
        # No context variables to pass to the template system, hence the
        # blank dictionary object...
        return render(request, 'login.html', {})


# Use the login_required() decorator to ensure only those logged in can access the view.
@login_required
def user_logout(request):
    # Since we know the user is logged in, we can now just log them out.
    logout(request)

    # Take the user back to the homepage.
    return HttpResponseRedirect('/')




   
