# frozen_string_literal: true

require 'spec_helper'

require 'mastoras/facade'

RSpec.describe Mastoras::Facade do
  it 'exists' do
  end

  it 'is constructible with a mastoroot Pathname' do
    expect { described_class.new Pathname.new '/somewhere/' }
      .not_to raise_error
  end

  it 'does not accept non-path-name roots' do
    expect { described_class.new '/somewhere/' }
      .to raise_error ArgumentError
  end
end
