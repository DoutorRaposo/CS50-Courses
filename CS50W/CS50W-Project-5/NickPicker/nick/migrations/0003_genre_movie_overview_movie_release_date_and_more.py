# Generated by Django 4.2.6 on 2024-01-09 22:20

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('nick', '0002_rename_movies_movie'),
    ]

    operations = [
        migrations.CreateModel(
            name='Genre',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=32)),
                ('tmdb_id', models.IntegerField()),
            ],
        ),
        migrations.AddField(
            model_name='movie',
            name='overview',
            field=models.TextField(blank=True),
        ),
        migrations.AddField(
            model_name='movie',
            name='release_date',
            field=models.DateTimeField(null=True),
        ),
        migrations.AddField(
            model_name='movie',
            name='tmdb_id',
            field=models.IntegerField(null=True),
        ),
        migrations.AddField(
            model_name='movie',
            name='genre',
            field=models.ManyToManyField(blank=True, related_name='genres', to='nick.genre'),
        ),
    ]