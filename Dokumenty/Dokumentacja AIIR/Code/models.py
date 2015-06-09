class Task(models.Model):
    userID = models.ForeignKey('auth.User')
    numberOfPoints = models.BigIntegerField(default=0)
    numberOfThreads = models.IntegerField(default=1)
    add_date = models.DateTimeField(default=timezone.now)


class DoneTask(models.Model):
    userID = models.ForeignKey('auth.User')
    numberOfPoints = models.BigIntegerField(default=0)
    add_date = models.DateTimeField(default=timezone.now)
    value = models.TextField();



class UserProfile(models.Model):
    user = models.OneToOneField(User)
    
    def __unicode__(self):
        return self.user.username