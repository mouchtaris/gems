# frozen_string_literal: true

require 'spec_helper'
require 'util/deco'

RSpec.describe Util::Deco do
  let(:extender) do
    Class.new(described_class) do |clazz|
      clazz.const_set :SCHEMA, Class.new
    end
  end

  subject(:instance) { extender.new(value) }

  describe 'initialized with a value of SCHEMA' do
    let(:value) { extender.schema.new }
    it { expect { subject }.not_to raise_error }
  end

  describe 'initialized with another value' do
    let(:value) { '' }
    it { expect { subject }.to raise_error ArgumentError }
  end
end
