# Generated by Django 4.2.6 on 2023-11-06 20:47

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0012_alter_bid_options_rename_bid_bid_value'),
    ]

    operations = [
        migrations.AlterField(
            model_name='bid',
            name='value',
            field=models.DecimalField(decimal_places=2, max_digits=10, verbose_name='Bid'),
        ),
        migrations.AlterField(
            model_name='comment',
            name='body',
            field=models.TextField(verbose_name='Comment'),
        ),
        migrations.RemoveField(
            model_name='watchlist',
            name='listing',
        ),
        migrations.AddField(
            model_name='watchlist',
            name='listing',
            field=models.ManyToManyField(related_name='watchlist', to='auctions.listing'),
        ),
    ]